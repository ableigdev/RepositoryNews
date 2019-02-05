#include "GitRepositoryFactory.h"
#include "GitRepositoryImpl.h"

interfaces::IRepository* git_impl::GitRepositoryFactory::createRepository(
        const std::string& url, 
        const helpers::secure_string& user, 
        const helpers::secure_string& pass, 
        bool flag)
{
    return new GitRepositoryImpl(url, user, pass, flag);
}
