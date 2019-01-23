#include "GitRepositoryImpl.h"

GitRepositoryImpl::GitRepositoryImpl(const std::string& url, const helpers::secure_string& user, const helpers::secure_string& pass, bool flag)
: m_GitRepositoryTypeImpl(new GitRepositoryTypeImpl(url, user, pass, flag))
{

}

std::vector<std::string> GitRepositoryImpl::getBranchName() const
{
    return m_GitRepositoryTypeImpl->getNameOfBranches();
}

size_t GitRepositoryImpl::getNumberOfBranches() const
{
    return m_GitRepositoryTypeImpl->getNumberOfBranches();
}

void GitRepositoryImpl::setCurrentBranch(size_t index)
{
    m_GitRepositoryTypeImpl->setCurrentBranch(index);
}

std::vector<helpers::commit> GitRepositoryImpl::getLastCommit()
{
    return m_GitRepositoryTypeImpl->getLastCommit();
}

void GitRepositoryImpl::prepareBranches()
{
    m_GitRepositoryTypeImpl->prepareBranches();
}

void GitRepositoryImpl::prepareRepository()
{
    m_GitRepositoryTypeImpl->prepareDataOfRepository();
}

void GitRepositoryImpl::saveConfig()
{
    m_GitRepositoryTypeImpl->saveConfig();
}

size_t GitRepositoryImpl::getCurrentBranchIndex() const
{
    return m_GitRepositoryTypeImpl->getCurrentBranchIndex();
}

std::string GitRepositoryImpl::getCurrentBranchName() const
{
    return m_GitRepositoryTypeImpl->getCurrentBranchName();
}

std::string GitRepositoryImpl::getRepositoryName() const
{
    return m_GitRepositoryTypeImpl->getRepositoryName();
}

