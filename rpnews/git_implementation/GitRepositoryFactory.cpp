#include "GitRepositoryFactory.h"
#include "GitRepositoryImpl.h"

std::unique_ptr<interfaces::IRepository> git_impl::GitRepositoryFactory::createRepository(
        const std::string& url, 
        const helpers::secure_string& user, 
        const helpers::secure_string& pass, 
        bool flag)
{
    return std::make_unique<git_impl::GitRepositoryImpl>(url, user, pass, flag);
}
