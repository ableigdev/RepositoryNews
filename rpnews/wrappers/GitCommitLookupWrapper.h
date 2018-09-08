#ifndef RPNEWS_GITCOMMITLOOKUPWRAPPER_H
#define RPNEWS_GITCOMMITLOOKUPWRAPPER_H

#include "git2.h"
#include "RepositoryWrapper.h"

namespace git_wrapper
{
    class GitCommitLookupWrapper
    {
    public:
        GitCommitLookupWrapper(git_wrapper::RepositoryWrapper& repo, git_oid& oid);
        ~GitCommitLookupWrapper();
        git_commit* getPointer() const;

    private:
        git_commit* m_Commit = nullptr;
    };
}

#endif //RPNEWS_GITCOMMITLOOKUPWRAPPER_H
