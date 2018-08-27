#include "GitBranchIteratorWrapper.h"
#include <string>
#include <stdexcept>

git_wrapper::GitBranchIteratorWrapper::GitBranchIteratorWrapper(git_wrapper::RepositoryWrapper &repo)
{
    if (git_branch_iterator_new(&m_BranchIterator, repo.getPointer(), GIT_BRANCH_REMOTE) != 0)
    {
        const git_error* lastError = giterr_last();
        std::string error("problem with git_branch_iterator_new, error message : '");
        error += lastError->message;
        error += "'";
        throw std::logic_error(error);
    }
}

git_wrapper::GitBranchIteratorWrapper::~GitBranchIteratorWrapper()
{
    if (m_BranchIterator != nullptr)
    {
        git_branch_iterator_free(m_BranchIterator);
    }
}

git_branch_iterator* git_wrapper::GitBranchIteratorWrapper::getPointer() const
{
    return m_BranchIterator;
}