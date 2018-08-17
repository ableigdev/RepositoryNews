#ifndef RPNEWS_IREPOSITORYFACTORY_H
#define RPNEWS_IREPOSITORYFACTORY_H

#include "IRepository.h"

class IRepositoryFactory
{
public:
    IRepositoryFactory() = default;
    ~IRepositoryFactory() = default;
    virtual IRepository* createRepository() = 0;
};
#endif //RPNEWS_IREPOSITORYFACTORY_H
