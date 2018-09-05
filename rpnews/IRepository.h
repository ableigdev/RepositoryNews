#ifndef RPNEWS_IREPOSITORY_H
#define RPNEWS_IREPOSITORY_H

#include <vector>
#include <string>
#include "rpnews_types.h"

class IRepository
{
public:
    IRepository() = default;
    virtual ~IRepository() = default;
    virtual std::vector<std::string> getBranchName() const = 0;
    virtual size_t getNumberOfBranches() const = 0;
    virtual void setCurrentBranch(size_t) = 0;
    virtual std::vector<commit> getLastCommit() = 0;
    virtual void prepareRepository() = 0;
    virtual void prepareBranches() = 0;
};

#endif //RPNEWS_IREPOSITORY_H
