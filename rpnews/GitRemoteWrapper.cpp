#include "GitRemoteWrapper.h"
#include "ErrorMessageMaker.h"
#include <stdexcept>

git_wrapper::GitRemoteWrapper::GitRemoteWrapper(git_wrapper::RepositoryWrapper &repo, const std::string& url)
{
    check(repo, url);
}

git_wrapper::GitRemoteWrapper::~GitRemoteWrapper()
{
    if (m_Remote != nullptr)
    {
        git_remote_free(m_Remote);
    }
}

bool git_wrapper::GitRemoteWrapper::create(git_wrapper::RepositoryWrapper& repo, const std::string& url)
{
    if (m_Remote == nullptr)
    {
        check(repo, url);
        return true;
    }
    return false;
}

void git_wrapper::GitRemoteWrapper::check(git_wrapper::RepositoryWrapper& repo, const std::string& url)
{
    if (git_remote_create(&m_Remote, repo.getPointer(), "origin", url.data()) != 0)
    {
        throw std::logic_error(ErrorMessageMaker::getErrorMessage("git_remote_create"));
    }
}

git_remote* git_wrapper::GitRemoteWrapper::getPointer() const
{
    return m_Remote;
}