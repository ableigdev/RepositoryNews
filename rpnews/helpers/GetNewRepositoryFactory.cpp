#include "GetNewRepositoryFactory.h"
#include "git_implementation/GitRepositoryFactory.h"

std::unique_ptr<interfaces::IRepositoryFactory> helpers::getNewRepositoryFactory(int index)
{
    switch (index)
    {
        case 0:
        {
            return std::make_unique<git_impl::GitRepositoryFactory>();
        }
        default:
        {
            return nullptr;
        }
    }
}
