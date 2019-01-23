#ifndef RPNEWS_GITREPOSITORYFACTORY_H
#define RPNEWS_GITREPOSITORYFACTORY_H

#include "rpnews/interfaces/IRepositoryFactory.h"

class GitRepositoryFactory : public IRepositoryFactory
{
public:
    GitRepositoryFactory() = default;
    virtual ~GitRepositoryFactory() = default;
    virtual IRepository* createRepository(const std::string& url, const helpers::secure_string& user, const helpers::secure_string& pass, bool flag);
};

#endif //RPNEWS_GITREPOSITORYFACTORY_H
