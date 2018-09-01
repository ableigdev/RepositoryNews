#ifndef RPNEWS_IREPOSITORYTYPE_H
#define RPNEWS_IREPOSITORYTYPE_H

#include <vector>
#include <string>

class IRepositoryType
{
public:
    IRepositoryType() = default;
    virtual ~IRepositoryType() = default;
    virtual std::vector<std::string> getNameOfBranches() const = 0;
    virtual size_t getNumberOfBranches() const = 0;
};

#endif //RPNEWS_IREPOSITORYTYPE_H
