#include "GitRepositoryFactory.h"
#include "GitRepositoryImpl.h"

IRepository* GitRepositoryFactory::createRepository(const std::string& url, const secure_string& user, const secure_string& pass) 
{
    return new GitRepositoryImpl(url, user, pass);
}