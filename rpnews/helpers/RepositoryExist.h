#ifndef REPOSITORYEXIST_H
#define REPOSITORYEXIST_H

#include <stdexcept>

class RepositoryExist : public std::logic_error
{
public:
    RepositoryExist(const std::string& name)
        : std::logic_error("Repository '" + name + "' is exist!")
    {

    }
};

#endif // REPOSITORYEXIST_H
