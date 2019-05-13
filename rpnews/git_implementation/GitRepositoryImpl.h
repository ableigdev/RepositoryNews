#ifndef RPNEWS_GITREPOSITORYIMPL_H
#define RPNEWS_GITREPOSITORYIMPL_H

#include "interfaces/IRepository.h"
#include "GitRepositoryTypeImpl.h"
#include <memory>

namespace git_impl
{
    class GitRepositoryImpl : public interfaces::IRepository
    {
    public:
        GitRepositoryImpl(const std::string& url, 
            const helpers::secure_string& user, 
            const helpers::secure_string& pass, 
            bool flag);
        virtual ~GitRepositoryImpl() override = default;
        virtual std::vector<std::string> getBranchName() const override;
        virtual size_t getNumberOfBranches() const override;
        virtual void setCurrentBranch(size_t) override;
        virtual size_t getCurrentBranchIndex() const override;
        virtual std::string getCurrentBranchName() const override;
        virtual std::string getRepositoryName() const override;
        virtual std::vector<helpers::commit> getLastCommit() override;
        virtual void prepareRepository() override;
        virtual void prepareBranches() override;
        virtual void saveConfig() override;

    private:
        std::unique_ptr<GitRepositoryTypeImpl> m_GitRepositoryTypeImpl;
    };
}

#endif //RPNEWS_GITREPOSITORYIMPL_H
