#ifndef RPNEWS_GITREPOSITORYTYPEIMPL_H
#define RPNEWS_GITREPOSITORYTYPEIMPL_H

#include <string>
#include "git2.h"
#include "IRepositoryType.h"
#include "rpnews_types.h"
#include "LibraryWrapper.h"
#include "RepositoryWrapper.h"
#include "GitRemoteWrapper.h"

class GitRepositoryTypeImpl : public IRepositoryType
{
public:
    GitRepositoryTypeImpl(const std::string& url, const secure_string& user, const secure_string& pass);
    virtual ~GitRepositoryTypeImpl() = default;

private:
    std::string getRepositoryFolderName(const std::string& url);
    int userpassGitCredCb(git_cred** cred, const char* url, const char* usernameFromUrl, unsigned int allowedTypes, void* payload);
    void connect();

private:
    int m_Counter = 0;
    git_wrapper::LibraryWrapper m_LibraryWrapper;
    git_wrapper::RepositoryWrapper m_Repository;
    git_wrapper::GitRemoteWrapper m_Remote;
    secure_string m_Username;
    secure_string m_Password;
};

#endif //RPNEWS_GITREPOSITORYTYPEIMPL_H
