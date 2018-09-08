#include "GitRevwalkWrapper.h"
#include "rpnews/helpers/ErrorMessageMaker.h"
#include <string>
#include <stdexcept>

git_wrapper::GitRevwalkWrapper::GitRevwalkWrapper(git_wrapper::RepositoryWrapper &repo)
{
    if (git_revwalk_new(&m_Revwalk, repo.getPointer()) != 0)
    {
        throw std::logic_error(ErrorMessageMaker::getErrorMessage("git_revwalk_new"));
    }
}

git_wrapper::GitRevwalkWrapper::~GitRevwalkWrapper()
{
    if (m_Revwalk != nullptr)
    {
        git_revwalk_free(m_Revwalk);
    }
}

git_revwalk* git_wrapper::GitRevwalkWrapper::getPointer() const
{
    return m_Revwalk;
}