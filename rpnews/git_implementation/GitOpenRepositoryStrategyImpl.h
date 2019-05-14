#ifndef RPNEWS_GITOPENREPOSITORYSTRATEGYIMPL_H
#define RPNEWS_GITOPENREPOSITORYSTRATEGYIMPL_H

#include "interfaces/IStrategy.h"
#include "helpers/ConfigChecker.h"

namespace git_impl
{
    class GitOpenRepositoryStrategyImpl : public interfaces::IStrategy
    {
    public:
        GitOpenRepositoryStrategyImpl() = default;
        virtual ~GitOpenRepositoryStrategyImpl() override = default;
        virtual void raiseRepository(std::string* name, const std::string& url, git_wrapper::RepositoryWrapper* repository, git_wrapper::GitRemoteWrapper* remote) override;
    };
}

#endif //RPNEWS_GITOPENREPOSITORYSTRATEGYIMPL_H
