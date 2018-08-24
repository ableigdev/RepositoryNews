#include "LibraryWrapper.h"
#include "git2.h"

LibraryWrapper::LibraryWrapper()
{
    git_libgit2_init();
}

LibraryWrapper::~LibraryWrapper()
{
    git_libgit2_shutdown();
}