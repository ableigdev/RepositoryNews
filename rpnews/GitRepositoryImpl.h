#ifndef RPNEWS_GITREPOSITORYIMPL_H
#define RPNEWS_GITREPOSITORYIMPL_H

#include "IRepository.h"
#include "SecureAllocator.h"
#include "GitRepositoryTypeImpl.h"

class GitRepositoryImpl : public IRepository
{
public:
    GitRepositoryImpl(const std::string& url, const secure_string& user, const secure_string& pass);
    virtual ~GitRepositoryImpl() = default;
    virtual std::vector<std::string> getBranchName() const;
    virtual size_t getNumberOfBranches() const;
    virtual void setCurrentBranch(size_t);

private:
    GitRepositoryTypeImpl m_GitRepositoryTypeImpl;
};


#endif //RPNEWS_GITREPOSITORYIMPL_H
