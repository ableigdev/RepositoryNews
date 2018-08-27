#include "GitCommitLookupWrapper.h"
#include <string>
#include <stdexcept>

git_wrapper::GitCommitLookupWrapper::GitCommitLookupWrapper(git_wrapper::RepositoryWrapper &repo, git_oid &oid)
{
    if (git_commit_lookup(&m_Commit, repo.getPointer(), &oid) != 0)
    {
        const git_error* lastError = giterr_last();
        std::string error("problem with git_commit_lookup, error message: '");
        error += lastError->message;
        error += "'";
        throw std::logic_error(error);
    }
}

git_wrapper::GitCommitLookupWrapper::~GitCommitLookupWrapper()
{
    if (m_Commit != 0)
    {
        git_commit_free(m_Commit);
    }
}

git_commit* git_wrapper::GitCommitLookupWrapper::getPointer() const
{
    return m_Commit;
}