#ifndef RPNEWS_GITREPOSITORYTYPEIMPL_H
#define RPNEWS_GITREPOSITORYTYPEIMPL_H

#include <string>
#include "rpnews/interfaces/IRepositoryType.h"
#include "rpnews/helpers/rpnews_types.h"
#include "rpnews/wrappers/LibraryWrapper.h"
#include "rpnews/wrappers/RepositoryWrapper.h"
#include "rpnews/wrappers/GitRemoteWrapper.h"
#include <QDebug>

class GitRepositoryTypeImpl : public IRepositoryType
{
public:
    GitRepositoryTypeImpl(const std::string& url, const secure_string& user, const secure_string& pass);
    virtual ~GitRepositoryTypeImpl() = default;
    virtual std::vector<std::string> getNameOfBranches() const;
    virtual size_t getNumberOfBranches() const;
    virtual std::vector<commit> getLastCommit();
    virtual void setCurrentBranch(size_t index);
    virtual void prepareDataOfRepository();
    virtual void prepareBranches();

private:
    std::string getRepositoryFolderName(const std::string& url);
    static int userPassGitCredCb(git_cred** cred, const char* url, const char* usernameFromUrl, unsigned int allowedTypes, void *payload);
    int onGitCallBack(git_cred** cred, const char* url, const char* username_from_url, unsigned int allowed_types);
    static int progressCb(const char* str, int len, void* data);
    int onProgressCb(const char* str, int len);
    std::vector<commit> checkNewCommit();
    void connect();
    void fetchData();
    void changeHead();
    std::string getRefspecs();

private:
    int m_Counter;
    size_t m_CurrentBranch;
    bool m_WasData;
    git_wrapper::LibraryWrapper m_LibraryWrapper;
    git_wrapper::RepositoryWrapper m_Repository;
    git_wrapper::GitRemoteWrapper m_Remote;
    secure_string m_Username;
    secure_string m_Password;
    git_fetch_options m_FetchOptions;
    std::vector<std::string> m_NameOfBranches {};
};

#endif //RPNEWS_GITREPOSITORYTYPEIMPL_H
