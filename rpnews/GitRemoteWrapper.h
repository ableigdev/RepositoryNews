#ifndef RPNEWS_GITREMOTEWRAPPER_H
#define RPNEWS_GITREMOTEWRAPPER_H

#include "git2.h"
#include "RepositoryWrapper.h"
#include <string>

namespace git_wrapper
{
    class GitRemoteWrapper
    {
    public:
        GitRemoteWrapper(git_wrapper::RepositoryWrapper& repo, const std::string& url);
        ~GitRemoteWrapper();
        git_remote* getPointer() const;

    private:
        git_remote* m_Remote = nullptr;
    };
}

#endif //RPNEWS_GITREMOTEWRAPPER_H
