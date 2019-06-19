#include <regex>
#include <stdexcept>
#include <functional>
#include <memory>
#include <chrono>
#include <filesystem>
#include "GitRepositoryTypeImpl.h"
#include "wrappers/GitBranchIteratorWrapper.h"
#include "wrappers/GitReferenceWrapper.h"
#include "wrappers/GitRevwalkWrapper.h"
#include "wrappers/GitCommitLookupWrapper.h"
#include "helpers/ConfigChecker.h"
#include "helpers/ErrorMessageMaker.h"
#include "helpers/SaveConfig.h"

git_impl::GitRepositoryTypeImpl::GitRepositoryTypeImpl(const std::string &url, const helpers::secure_string& user, const helpers::secure_string& pass, std::unique_ptr<interfaces::IStrategy>&& strategy)
: m_Counter(0),
m_CurrentBranch(0),
m_WasData(false)
{
    if (strategy == nullptr)
    {
        throw std::logic_error("Bad strategy");
    }

    strategy->raiseRepository(&m_RepositoryName, url, &m_Repository, &m_Remote);
    m_Username = user;
    m_Password = pass;
    m_FetchOptions = GIT_FETCH_OPTIONS_INIT;
    m_FetchOptions.callbacks.credentials = &GitRepositoryTypeImpl::userPassGitCredCb;
    m_FetchOptions.callbacks.payload = this; // You'll get that pointer back as the payload parameter
    m_FetchOptions.callbacks.sideband_progress = &GitRepositoryTypeImpl::progressCb;
    connect();
    m_Counter = 0;
    m_NameOfBranches.emplace_back("origin/*");
}

int git_impl::GitRepositoryTypeImpl::userPassGitCredCb(git_cred** cred, const char* url, const char* usernameFromUrl,
                                             unsigned int allowedTypes, void* payload)
{
    auto self = static_cast<GitRepositoryTypeImpl*>(payload);
    return self->onGitCallBack(cred, url, usernameFromUrl, allowedTypes);
}

int git_impl::GitRepositoryTypeImpl::onGitCallBack(git_cred** cred, const char* url, const char* username_from_url, unsigned int allowed_types)
{
    Q_UNUSED(url);
    Q_UNUSED(username_from_url);
    if (m_Counter > 0)
    {
        throw std::logic_error("Invalid credential");
    }
    if ((allowed_types & GIT_CREDTYPE_USERPASS_PLAINTEXT) != 0)
    {
        ++m_Counter;
        return git_cred_userpass_plaintext_new(cred, m_Username.data(), m_Password.data());
    }
    else
    {
        return -1;
    }
}

int git_impl::GitRepositoryTypeImpl::progressCb(const char* str, int len, void* data)
{
    auto self = static_cast<GitRepositoryTypeImpl*>(data);
    return self->onProgressCb(str, len);
}

int git_impl::GitRepositoryTypeImpl::onProgressCb(const char* str, int len)
{
    Q_UNUSED(str);
    Q_UNUSED(len);
    m_WasData = true;
    return 0;
}

void git_impl::GitRepositoryTypeImpl::connect()
{
    if (git_remote_connect(m_Remote.getPointer(), GIT_DIRECTION_FETCH, &m_FetchOptions.callbacks, nullptr, nullptr) != 0)
    {
        throw std::logic_error(helpers::ErrorMessageMaker::getErrorMessage("git_remote_connect"));
    }
}

std::vector<std::string> git_impl::GitRepositoryTypeImpl::getNameOfBranches() const
{
    return m_NameOfBranches;
}

size_t git_impl::GitRepositoryTypeImpl::getNumberOfBranches() const
{
    return m_NameOfBranches.size();
}

void git_impl::GitRepositoryTypeImpl::prepareBranches()
{
    git_wrapper::GitBranchIteratorWrapper branchIterator(m_Repository);
    git_reference* reference;
    git_branch_t type = GIT_BRANCH_REMOTE;
    std::vector<const char*> name(50);
    m_NameOfBranches.clear();
    m_NameOfBranches.emplace_back("origin/*");

    while (git_branch_next(&reference, &type, branchIterator.getPointer()) != GIT_ITEROVER)
    {
        git_wrapper::GitReferenceWrapper referenceWrapper(reference);
        if (git_branch_name(&name.at(0), referenceWrapper.getPointer()) != 0)
        {
            throw std::logic_error(helpers::ErrorMessageMaker::getErrorMessage("git_branch_next"));
        }
        m_NameOfBranches.emplace_back(std::string(name.at(0)));
    }
}

std::vector<helpers::commit> git_impl::GitRepositoryTypeImpl::checkNewCommit()
{
    std::vector<helpers::commit> result {};
    git_wrapper::GitRevwalkWrapper revwalk(m_Repository);
    git_revwalk_sorting(revwalk.getPointer(), GIT_SORT_TOPOLOGICAL | GIT_SORT_TIME);
    git_revwalk_push_head(revwalk.getPointer());
    git_oid oid;

    if (git_revwalk_next(&oid, revwalk.getPointer()) == 0)
    {
        git_wrapper::GitCommitLookupWrapper lastCommit(m_Repository, oid);
        helpers::commit newCommit;
        newCommit.author = git_commit_author(lastCommit.getPointer())->name;
        newCommit.message = git_commit_message(lastCommit.getPointer());
        auto datetime = git_commit_time(lastCommit.getPointer());
        newCommit.date_time = std::ctime(&datetime);

        result.emplace_back(newCommit);
    }

    return result;
}

std::string git_impl::GitRepositoryTypeImpl::getRefspecs()
{
    std::cmatch cm;
    std::regex regVal(R"(origin\/([a-zA-Z0-9\/\._-]+|\*{1}))");
    std::regex_search(m_NameOfBranches[m_CurrentBranch].data(), cm, regVal);
    auto name = cm[1].str();
    std::string refspecs("+refs/heads/");
    refspecs += name;
    refspecs += ":refs/remotes/origin/";
    refspecs += name;
    return refspecs;
}

void git_impl::GitRepositoryTypeImpl::fetchData()
{
    auto refspecs = getRefspecs();
    std::vector<char *> arr(refspecs.size());
    arr.at(0) = &refspecs.at(0);
    git_strarray refs = { &arr.at(0), 1 };

    if (git_remote_fetch(m_Remote.getPointer(), &refs, &m_FetchOptions, nullptr) != 0)
    {
        throw std::logic_error(helpers::ErrorMessageMaker::getErrorMessage("git_remote_fetch"));
    }
    m_Counter = 0;
}

void git_impl::GitRepositoryTypeImpl::changeHead()
{
    std::filesystem::path currentPath(git_repository_workdir(m_Repository.getPointer()));
    currentPath /= ".git";
    std::filesystem::remove(currentPath / "HEAD");
    std::filesystem::rename(currentPath / "FETCH_HEAD", currentPath / "HEAD");
}

std::vector<helpers::commit> git_impl::GitRepositoryTypeImpl::getLastCommit()
{
    fetchData();
    if (m_WasData)
    {
        m_WasData = false;
        changeHead();
        return checkNewCommit();
    }
    return {};
}

void git_impl::GitRepositoryTypeImpl::setCurrentBranch(size_t index)
{
    if (index < m_NameOfBranches.size())
    {
        m_CurrentBranch = index;
        m_WasData = true;
    }
    else
    {
        throw std::logic_error("Out of range in 'setCurrentBranch' method");
    }
}

void git_impl::GitRepositoryTypeImpl::prepareDataOfRepository()
{
    fetchData();
}

void git_impl::GitRepositoryTypeImpl::saveConfig()
{
    if (m_Repository.getPointer() != nullptr)
    {
        helpers::SaveConfig::save(git_repository_workdir(m_Repository.getPointer()), helpers::TypeRepository::Git, m_Username, m_Password);
    }
}

size_t git_impl::GitRepositoryTypeImpl::getCurrentBranchIndex() const
{
    return m_CurrentBranch;
}

std::string git_impl::GitRepositoryTypeImpl::getCurrentBranchName() const
{
    return m_NameOfBranches[m_CurrentBranch];
}

std::string git_impl::GitRepositoryTypeImpl::getRepositoryName() const
{
    return m_RepositoryName;
}
