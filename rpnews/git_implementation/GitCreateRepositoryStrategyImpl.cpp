#include "GitCreateRepositoryStrategyImpl.h"

void git_impl::GitCreateRepositoryStrategyImpl::raiseRepository(std::string *name, const std::string &url, git_wrapper::RepositoryWrapper *repository, git_wrapper::GitRemoteWrapper *remote)
{
    *name = helpers::ConfigChecker::getRepositoryFolderName(url);
    if (name->empty())
    {
        throw std::logic_error("Invalid url");
    }
    auto path = helpers::ConfigChecker::checkAndGetFinalPath(*name);
    repository->create(path);
    remote->create(*repository, url);
}
