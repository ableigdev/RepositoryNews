#ifndef RPNEWS_ISTRATEGY_H
#define RPNEWS_ISTRATEGY_H

#include <string>
#include "wrappers/GitRemoteWrapper.h"
#include "wrappers/RepositoryWrapper.h"

namespace interfaces
{
    class IStrategy
    {
    public:
        IStrategy() = default;
        virtual ~IStrategy() = default;
        virtual void raiseRepository(std::string* name, const std::string& url, git_wrapper::RepositoryWrapper* repository, git_wrapper::GitRemoteWrapper* remote) = 0;
    };
}

#endif //RPNEWS_ISTRATEGY_H
