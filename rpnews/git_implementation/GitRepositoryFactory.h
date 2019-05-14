#ifndef RPNEWS_GITREPOSITORYFACTORY_H
#define RPNEWS_GITREPOSITORYFACTORY_H

#include "interfaces/IRepositoryFactory.h"
#include "interfaces/IStrategy.h"

namespace git_impl
{
    class GitRepositoryFactory : public interfaces::IRepositoryFactory
    {
    public:
        GitRepositoryFactory() = default;
        virtual ~GitRepositoryFactory() override = default;
        virtual std::unique_ptr<interfaces::IRepository> createRepository(
                const std::string& url, 
                const helpers::secure_string& user, 
                const helpers::secure_string& pass, 
                std::unique_ptr<interfaces::IStrategy>&& strategy) override;
    };
}
    
#endif //RPNEWS_GITREPOSITORYFACTORY_H
