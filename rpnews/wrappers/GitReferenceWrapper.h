#ifndef RPNEWS_GITREFERENCEWRAPPER_H
#define RPNEWS_GITREFERENCEWRAPPER_H

#include "git2.h"

namespace git_wrapper
{
    class GitReferenceWrapper
    {
    public:
        GitReferenceWrapper() = default;
        explicit GitReferenceWrapper(git_reference* ptr);
        ~GitReferenceWrapper();
        git_reference* getPointer() const;
        git_reference* getPointer();

    private:
        git_reference* m_Reference = nullptr;
    };
}

#endif //RPNEWS_GITREFERENCEWRAPPER_H
