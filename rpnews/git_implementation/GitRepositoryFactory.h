#ifndef RPNEWS_GITREPOSITORYFACTORY_H
#define RPNEWS_GITREPOSITORYFACTORY_H

#include "interfaces/IRepositoryFactory.h"

namespace git_impl
{
    class GitRepositoryFactory : public interfaces::IRepositoryFactory
    {
    public:
        GitRepositoryFactory() = default;
        virtual ~GitRepositoryFactory() = default;
        virtual interfaces::IRepository* createRepository(
                const std::string& url, 
                const helpers::secure_string& user, 
                const helpers::secure_string& pass, 
                bool flag);
    };
}
    
#endif //RPNEWS_GITREPOSITORYFACTORY_H
