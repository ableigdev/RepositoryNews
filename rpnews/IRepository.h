#ifndef RPNEWS_IREPOSITORY_H
#define RPNEWS_IREPOSITORY_H

#include <vector>
#include <string>

class IRepository
{
public:
    IRepository() = default;
    virtual ~IRepository() = default;
    virtual std::vector<std::string> getBranchName() const = 0;
    virtual size_t getNumberOfBranches() const = 0;
    virtual void setCurrentBranch(size_t) = 0;
};

#endif //RPNEWS_IREPOSITORY_H
