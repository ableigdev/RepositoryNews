#include "GitRevwalkWrapper.h"
#include <string>
#include <stdexcept>

git_wrapper::GitRevwalkWrapper::GitRevwalkWrapper(git_wrapper::RepositoryWrapper &repo)
{
    if (git_revwalk_new(&m_Revwalk, repo.getPointer()) != 0)
    {
        const git_error* lastError = giterr_last();
        std::string error("problem with git_revwalk_new, error message : '");
        error += lastError->message;
        error += "'";
        throw std::logic_error(error);
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