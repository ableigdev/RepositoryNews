#include "GitOpenRepositoryStrategyImpl.h"

void git_impl::GitOpenRepositoryStrategyImpl::raiseRepository(std::string& name, const std::string& url, git_wrapper::RepositoryWrapper& repository, git_wrapper::GitRemoteWrapper& remote)
{
    name = helpers::ConfigChecker::getRepositoryFolderNameFromPath(url);
    repository.open(url);
    remote.open(repository);
}
