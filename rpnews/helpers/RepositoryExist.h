#ifndef REPOSITORYEXIST_H
#define REPOSITORYEXIST_H

#include <stdexcept>

namespace helpers
{
    class RepositoryExist : public std::logic_error
    {
    public:
        explicit RepositoryExist(const std::string& name)
            : std::logic_error("Repository '" + name + "' is exist!")
        {

        }
    };
}

#endif // REPOSITORYEXIST_H
