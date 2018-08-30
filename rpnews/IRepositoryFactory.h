#ifndef RPNEWS_IREPOSITORYFACTORY_H
#define RPNEWS_IREPOSITORYFACTORY_H

#include <string>
#include "IRepository.h"
#include "rpnews_types.h"

class IRepositoryFactory
{
public:
    IRepositoryFactory() = default;
    virtual ~IRepositoryFactory() = default;
    virtual IRepository* createRepository(const std::string& url, const secure_string& user, const secure_string& pass) = 0;
};
#endif //RPNEWS_IREPOSITORYFACTORY_H
