#ifndef GETNEWREPOSITORYFACTORY_H
#define GETNEWREPOSITORYFACTORY_H

#include <memory>
#include "interfaces/IRepositoryFactory.h"

namespace helpers
{
    std::unique_ptr<interfaces::IRepositoryFactory> getNewRepositoryFactory(int index);
}

#endif // GETNEWREPOSITORYFACTORY_H
