#include "GitRepositoryFactory.h"
#include "GitRepositoryImpl.h"

std::unique_ptr<interfaces::IRepository> git_impl::GitRepositoryFactory::createRepository(
        const std::string& url, 
        const helpers::secure_string& user, 
        const helpers::secure_string& pass, 
        std::unique_ptr<interfaces::IStrategy>&& strategy)
{
    return std::make_unique<git_impl::GitRepositoryImpl>(url, user, pass, std::move(strategy));
}
