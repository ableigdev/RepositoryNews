#ifndef RPNEWS_GITREPOSITORYTYPEIMPL_H
#define RPNEWS_GITREPOSITORYTYPEIMPL_H

#include <string>
#include "interfaces/IRepositoryType.h"
#include "helpers/rpnews_types.h"
#include "wrappers/LibraryWrapper.h"
#include "wrappers/RepositoryWrapper.h"
#include "wrappers/GitRemoteWrapper.h"
#include <QDebug>

class GitRepositoryTypeImpl : public IRepositoryType
{
public:
    GitRepositoryTypeImpl(const std::string& url, const helpers::secure_string& user, const helpers::secure_string& pass, bool flag);
    virtual ~GitRepositoryTypeImpl() = default;
    virtual std::vector<std::string> getNameOfBranches() const;
    virtual size_t getNumberOfBranches() const;
    virtual std::vector<helpers::commit> getLastCommit();
    virtual void setCurrentBranch(size_t index);
    virtual size_t getCurrentBranchIndex() const;
    virtual std::string getCurrentBranchName() const;
    virtual std::string getRepositoryName() const;
    virtual void prepareDataOfRepository();
    virtual void prepareBranches();
    virtual void saveConfig();

private:
    static int userPassGitCredCb(git_cred** cred, const char* url, const char* usernameFromUrl, unsigned int allowedTypes, void *payload);
    int onGitCallBack(git_cred** cred, const char* url, const char* username_from_url, unsigned int allowed_types);
    static int progressCb(const char* str, int len, void* data);
    int onProgressCb(const char* str, int len);
    std::vector<helpers::commit> checkNewCommit();
    void connect();
    void fetchData();
    void changeHead();
    std::string getRefspecs();

private:
    int m_Counter;
    size_t m_CurrentBranch;
    bool m_WasData;
    std::string m_RepositoryName {};
    git_wrapper::LibraryWrapper m_LibraryWrapper;
    git_wrapper::RepositoryWrapper m_Repository;
    git_wrapper::GitRemoteWrapper m_Remote;
    helpers::secure_string m_Username;
    helpers::secure_string m_Password;
    git_fetch_options m_FetchOptions;
    std::vector<std::string> m_NameOfBranches {};
};

#endif //RPNEWS_GITREPOSITORYTYPEIMPL_H
