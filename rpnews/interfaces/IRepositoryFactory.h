#ifndef RPNEWS_IREPOSITORYFACTORY_H
#define RPNEWS_IREPOSITORYFACTORY_H

#include <string>
#include "IRepository.h"
#include "helpers/rpnews_types.h"

namespace interfaces
{
    class IRepositoryFactory
    {
    public:
        IRepositoryFactory() = default;
        virtual ~IRepositoryFactory() = default;
        virtual IRepository* createRepository(const std::string& url, const helpers::secure_string& user, const helpers::secure_string& pass, bool flag) = 0;
    };
}

#endif //RPNEWS_IREPOSITORYFACTORY_H
