#include "GetNewRepositoryFactory.h"
#include "rpnews/git_implementation/GitRepositoryFactory.h"

IRepositoryFactory* helpers::getNewRepositoryFactory(int index)
{
    switch (index)
    {
        case 0:
        {
            return new GitRepositoryFactory();
        }
        default:
        {
            return nullptr;
        }
    }
}
