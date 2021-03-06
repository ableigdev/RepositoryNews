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
        GitRemoteWrapper() = default;
        ~GitRemoteWrapper();
        GitRemoteWrapper(const GitRemoteWrapper&) = delete;
        GitRemoteWrapper& operator=(const GitRemoteWrapper&) = delete;
        GitRemoteWrapper(GitRemoteWrapper&& remoteWrapper) noexcept;
        GitRemoteWrapper& operator=(GitRemoteWrapper&& remoteWrapper) noexcept;
        bool create(git_wrapper::RepositoryWrapper& repo, const std::string& url);
        bool open(git_wrapper::RepositoryWrapper& repo);
        git_remote* getPointer() const;

    private:
        void check(git_wrapper::RepositoryWrapper& repo, const std::string& url);

    private:
        git_remote* m_Remote = nullptr;
    };
}

#endif //RPNEWS_GITREMOTEWRAPPER_H
