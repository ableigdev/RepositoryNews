#include "RepositoryWrapper.h"
#include "helpers/ErrorMessageMaker.h"
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

git_wrapper::RepositoryWrapper::RepositoryWrapper(git_wrapper::RepositoryWrapper &&repositoryWrapper) noexcept
: m_Repo(repositoryWrapper.m_Repo)
{
    repositoryWrapper.m_Repo = nullptr;
}

git_wrapper::RepositoryWrapper& git_wrapper::RepositoryWrapper::operator=(git_wrapper::RepositoryWrapper&& repositoryWrapper) noexcept
{
    if (this != &repositoryWrapper)
    {
        m_Repo = repositoryWrapper.m_Repo;
        repositoryWrapper.m_Repo = nullptr;
    }
    return *this;
}

void git_wrapper::RepositoryWrapper::check(const std::string& path)
{
    if (git_repository_init(&m_Repo, path.data(), false) != 0)
    {
        throw std::logic_error(helpers::ErrorMessageMaker::getErrorMessage("git_repository_init"));
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

bool git_wrapper::RepositoryWrapper::open(const std::string& path)
{
    if (m_Repo == nullptr)
    {
        if (git_repository_open(&m_Repo, path.data()) != 0)
        {
            throw std::logic_error(helpers::ErrorMessageMaker::getErrorMessage("git_repository_open"));
        }
        return true;
    }
    return false;
}

git_repository* git_wrapper::RepositoryWrapper::getPointer() const
{
    return m_Repo;
}
