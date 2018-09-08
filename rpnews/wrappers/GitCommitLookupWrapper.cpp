#include "GitCommitLookupWrapper.h"
#include "rpnews/helpers/ErrorMessageMaker.h"
#include <string>
#include <stdexcept>

git_wrapper::GitCommitLookupWrapper::GitCommitLookupWrapper(git_wrapper::RepositoryWrapper &repo, git_oid &oid)
{
    if (git_commit_lookup(&m_Commit, repo.getPointer(), &oid) != 0)
    {
        throw std::logic_error(ErrorMessageMaker::getErrorMessage("git_commit_lookup"));
    }
}

git_wrapper::GitCommitLookupWrapper::~GitCommitLookupWrapper()
{
    if (m_Commit != nullptr)
    {
        git_commit_free(m_Commit);
    }
}

git_commit* git_wrapper::GitCommitLookupWrapper::getPointer() const
{
    return m_Commit;
}