#include "GitReferenceWrapper.h"

git_wrapper::GitReferenceWrapper::~GitReferenceWrapper()
{
    if (m_Reference != nullptr)
    {
        git_reference_free(m_Reference);
    }
}

git_reference* git_wrapper::GitReferenceWrapper::getPointer() const
{
    return m_Reference;
}