#include "GetNewRepositoryFactory.h"
#include "git_implementation/GitRepositoryFactory.h"

interfaces::IRepositoryFactory* helpers::getNewRepositoryFactory(int index)
{
    switch (index)
    {
        case 0:
        {
            return new git_impl::GitRepositoryFactory();
        }
        default:
        {
            return nullptr;
        }
    }
}
