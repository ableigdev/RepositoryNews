#include "GitRepositoryImpl.h"

GitRepositoryImpl::GitRepositoryImpl(const std::string& url, const secure_string& user, const secure_string& pass)
: m_GitRepositoryTypeImpl(url, user, pass)
{

}

std::vector<std::string> GitRepositoryImpl::getBranchName() const
{
    return m_GitRepositoryTypeImpl.getNameOfBranches();
}

size_t GitRepositoryImpl::getNumberOfBranches() const
{
    return m_GitRepositoryTypeImpl.getNumberOfBranches();
}

void GitRepositoryImpl::setCurrentBranch(size_t index)
{
    // TODO: Finish this method
}

