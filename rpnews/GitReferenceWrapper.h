#ifndef RPNEWS_GITREFERENCEWRAPPER_H
#define RPNEWS_GITREFERENCEWRAPPER_H

#include "git2.h"

namespace git_wrapper
{
    class GitReferenceWrapper
    {
    public:
        GitReferenceWrapper() = default;
        ~GitReferenceWrapper();
        git_reference* getPointer() const;

    private:
        git_reference* m_Reference = nullptr;
    };
}

#endif //RPNEWS_GITREFERENCEWRAPPER_H
