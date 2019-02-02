#ifndef GETNEWREPOSITORYFACTORY_H
#define GETNEWREPOSITORYFACTORY_H

#include "interfaces/IRepositoryFactory.h"

namespace helpers
{
    interfaces::IRepositoryFactory* getNewRepositoryFactory(int index);
}

#endif // GETNEWREPOSITORYFACTORY_H
