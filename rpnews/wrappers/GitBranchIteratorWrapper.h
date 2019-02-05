#ifndef RPNEWS_GITBRANCHITERATORWRAPPER_H
#define RPNEWS_GITBRANCHITERATORWRAPPER_H

#include "git2.h"
#include "RepositoryWrapper.h"

namespace git_wrapper
{
    class GitBranchIteratorWrapper
    {
    public:
        explicit GitBranchIteratorWrapper(git_wrapper::RepositoryWrapper& repo);
        ~GitBranchIteratorWrapper();
        git_branch_iterator* getPointer() const;

    private:
        git_branch_iterator* m_BranchIterator = nullptr;
    };
}

#endif //RPNEWS_GITBRANCHITERATORWRAPPER_H
