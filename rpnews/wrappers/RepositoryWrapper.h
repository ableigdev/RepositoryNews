#ifndef RPNEWS_REPOSITORYWRAPPER_H
#define RPNEWS_REPOSITORYWRAPPER_H

#include <string>
#include "git2.h"

namespace git_wrapper
{
    class RepositoryWrapper
    {
    public:
        RepositoryWrapper() = default;
        explicit RepositoryWrapper(const std::string& path);
        ~RepositoryWrapper();
        RepositoryWrapper(const RepositoryWrapper&) = delete;
        RepositoryWrapper& operator=(const RepositoryWrapper&) = delete;
        RepositoryWrapper(RepositoryWrapper&& repositoryWrapper) noexcept;
        RepositoryWrapper& operator=(RepositoryWrapper&& repositoryWrapper) noexcept;
        bool create(const std::string& path);
        bool open(const std::string& path);
        git_repository* getPointer() const;

    private:
        void check(const std::string& path);

    private:
        git_repository* m_Repo = nullptr;
    };
}

#endif //RPNEWS_REPOSITORYWRAPPER_H
