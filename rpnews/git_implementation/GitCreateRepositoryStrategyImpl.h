#ifndef RPNEWS_GITCREATEREPOSITORYSTRATEGYIMPL_H
#define RPNEWS_GITCREATEREPOSITORYSTRATEGYIMPL_H

#include <stdexcept>
#include "interfaces/IStrategy.h"
#include "helpers/ConfigChecker.h"

namespace git_impl
{
    class GitCreateRepositoryStrategyImpl : public interfaces::IStrategy
    {
    public:
        GitCreateRepositoryStrategyImpl() = default;
        virtual ~GitCreateRepositoryStrategyImpl() override = default;
        virtual void raiseRepository(std::string* name, const std::string& url, git_wrapper::RepositoryWrapper* repository, git_wrapper::GitRemoteWrapper* remote) override;
    };
}

#endif //RPNEWS_GITCREATEREPOSITORYSTRATEGYIMPL_H
