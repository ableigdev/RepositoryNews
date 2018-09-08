#include "RepositoryWrapper.h"
#include "rpnews/helpers/ErrorMessageMaker.h"
#include <stdexcept>

git_wrapper::RepositoryWrapper::RepositoryWrapper(const std::string& path)
{
    check(path);
}

git_wrapper::RepositoryWrapper::~RepositoryWrapper()
{
    if (m_Repo != nullptr)
    {
        git_repository_free(m_Repo);
    }
}

void git_wrapper::RepositoryWrapper::check(const std::string& path)
{
    if (git_repository_init(&m_Repo, path.data(), false) != 0)
    {
        throw std::logic_error(ErrorMessageMaker::getErrorMessage("git_repository_init"));
    }
}

bool git_wrapper::RepositoryWrapper::create(const std::string& path)
{
    if (m_Repo == nullptr)
    {
        check(path);
        return true;
    }
    return false;
}

git_repository* git_wrapper::RepositoryWrapper::getPointer() const
{
    return m_Repo;
}