#ifndef RPNEWS_GITREPOSITORYTYPEIMPL_H
#define RPNEWS_GITREPOSITORYTYPEIMPL_H

#include <string>
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

private:
    git_wrapper::LibraryWrapper m_LibraryWrapper;
    git_wrapper::RepositoryWrapper m_Repository;
    git_wrapper::GitRemoteWrapper m_Remote;
};


#endif //RPNEWS_GITREPOSITORYTYPEIMPL_H
