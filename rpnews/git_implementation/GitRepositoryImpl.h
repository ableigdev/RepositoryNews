#ifndef RPNEWS_GITREPOSITORYIMPL_H
#define RPNEWS_GITREPOSITORYIMPL_H

#include "interfaces/IRepository.h"
#include "GitRepositoryTypeImpl.h"
#include <memory>

class GitRepositoryImpl : public IRepository
{
public:
    GitRepositoryImpl(const std::string& url, const helpers::secure_string& user, const helpers::secure_string& pass, bool flag);
    virtual ~GitRepositoryImpl() = default;
    virtual std::vector<std::string> getBranchName() const;
    virtual size_t getNumberOfBranches() const;
    virtual void setCurrentBranch(size_t);
    virtual size_t getCurrentBranchIndex() const;
    virtual std::string getCurrentBranchName() const;
    virtual std::string getRepositoryName() const;
    virtual std::vector<helpers::commit> getLastCommit();
    virtual void prepareRepository();
    virtual void prepareBranches();
    virtual void saveConfig();

private:
    std::unique_ptr<GitRepositoryTypeImpl> m_GitRepositoryTypeImpl;
};


#endif //RPNEWS_GITREPOSITORYIMPL_H
