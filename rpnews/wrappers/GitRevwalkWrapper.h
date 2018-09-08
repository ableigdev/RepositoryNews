#ifndef RPNEWS_GITREVWALKWRAPPER_H
#define RPNEWS_GITREVWALKWRAPPER_H

#include "git2.h"
#include "RepositoryWrapper.h"

namespace git_wrapper
{
    class GitRevwalkWrapper
    {
    public:
        explicit GitRevwalkWrapper(RepositoryWrapper& repo);
        ~GitRevwalkWrapper();
        git_revwalk* getPointer() const;

    private:
        git_revwalk* m_Revwalk = nullptr;
    };
}

#endif //RPNEWS_GITREVWALKWRAPPER_H
