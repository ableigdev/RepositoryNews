#ifndef RPNEWS_GITREPOSITORYFACTORY_H
#define RPNEWS_GITREPOSITORYFACTORY_H

#include "IRepositoryFactory.h"

class GitRepositoryFactory : public IRepositoryFactory
{
public:
    GitRepositoryFactory() = default;
    virtual ~GitRepositoryFactory() = default;
    virtual IRepository* createRepository();
};

#endif //RPNEWS_GITREPOSITORYFACTORY_H
