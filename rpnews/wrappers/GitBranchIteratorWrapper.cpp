#include "GitBranchIteratorWrapper.h"
#include "helpers/ErrorMessageMaker.h"
#include <string>
#include <stdexcept>

git_wrapper::GitBranchIteratorWrapper::GitBranchIteratorWrapper(git_wrapper::RepositoryWrapper &repo)
{
    if (git_branch_iterator_new(&m_BranchIterator, repo.getPointer(), GIT_BRANCH_REMOTE) != 0)
    {
        throw std::logic_error(helpers::ErrorMessageMaker::getErrorMessage("git_branch_iterator_new"));
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
