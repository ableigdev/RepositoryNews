#include "GitRepositoryImpl.h"

git_impl::GitRepositoryImpl::GitRepositoryImpl(
    const std::string& url, 
    const helpers::secure_string& user, 
    const helpers::secure_string& pass, 
    std::unique_ptr<interfaces::IStrategy>&& strategy)
    : m_GitRepositoryTypeImpl(new GitRepositoryTypeImpl(url, user, pass, std::move(strategy)))
{

}

std::vector<std::string> git_impl::GitRepositoryImpl::getBranchName() const
{
    return m_GitRepositoryTypeImpl->getNameOfBranches();
}

size_t git_impl::GitRepositoryImpl::getNumberOfBranches() const
{
    return m_GitRepositoryTypeImpl->getNumberOfBranches();
}

void git_impl::GitRepositoryImpl::setCurrentBranch(size_t index)
{
    m_GitRepositoryTypeImpl->setCurrentBranch(index);
}

std::vector<helpers::commit> git_impl::GitRepositoryImpl::getLastCommit()
{
    return m_GitRepositoryTypeImpl->getLastCommit();
}

void git_impl::GitRepositoryImpl::prepareBranches()
{
    m_GitRepositoryTypeImpl->prepareBranches();
}

void git_impl::GitRepositoryImpl::prepareRepository()
{
    m_GitRepositoryTypeImpl->prepareDataOfRepository();
}

void git_impl::GitRepositoryImpl::saveConfig()
{
    m_GitRepositoryTypeImpl->saveConfig();
}

size_t git_impl::GitRepositoryImpl::getCurrentBranchIndex() const
{
    return m_GitRepositoryTypeImpl->getCurrentBranchIndex();
}

std::string git_impl::GitRepositoryImpl::getCurrentBranchName() const
{
    return m_GitRepositoryTypeImpl->getCurrentBranchName();
}

std::string git_impl::GitRepositoryImpl::getRepositoryName() const
{
    return m_GitRepositoryTypeImpl->getRepositoryName();
}

