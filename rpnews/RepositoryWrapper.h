#ifndef RPNEWS_REPOSITORYWRAPPER_H
#define RPNEWS_REPOSITORYWRAPPER_H

#include <string>
#include "git2.h"

namespace git_wrapper
{
    class RepositoryWrapper
    {
    public:
        explicit RepositoryWrapper(const std::string& path);
        ~RepositoryWrapper();
        git_repository* getPointer() const;

    private:
        git_repository* m_Repo = nullptr;
    };
}

#endif //RPNEWS_REPOSITORYWRAPPER_H
