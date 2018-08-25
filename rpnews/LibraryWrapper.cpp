#include "LibraryWrapper.h"
#include "git2.h"

git_wrapper::LibraryWrapper::LibraryWrapper()
{
    git_libgit2_init();
}

git_wrapper::LibraryWrapper::~LibraryWrapper()
{
    git_libgit2_shutdown();
}