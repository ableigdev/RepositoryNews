#ifndef RPNEWS_IREPOSITORYTYPE_H
#define RPNEWS_IREPOSITORYTYPE_H

#include <vector>
#include <string>
#include "rpnews/helpers/rpnews_types.h"

class IRepositoryType
{
public:
    IRepositoryType() = default;
    virtual ~IRepositoryType() = default;
    virtual std::vector<std::string> getNameOfBranches() const = 0;
    virtual size_t getNumberOfBranches() const = 0;
    virtual std::vector<commit> getLastCommit() = 0;
    virtual void setCurrentBranch(size_t) = 0;
    virtual void prepareDataOfRepository() = 0;
    virtual void prepareBranches() = 0;
    virtual void saveConfig() = 0;
};

#endif //RPNEWS_IREPOSITORYTYPE_H
