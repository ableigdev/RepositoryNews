#ifndef RPNEWS_RPNEWS_TYPES_H
#define RPNEWS_RPNEWS_TYPES_H

#include "SecureAllocator.h"
#include <string>

typedef std::basic_string<char, std::char_traits<char>, secure::SecureAllocator<char>> secure_string;

struct commit
{
    std::string author;
    std::string message;
    std::string date_time;
};

enum TypeRepository { Git };

struct GetRepositoryInfo
{
    std::string path {};
    int type = -1;
    secure_string user {};
    secure_string pass {};
    std::string branchName {};
    int branchIndex = -1;
    int timeInterval = -1;
};

#endif //RPNEWS_RPNEWS_TYPES_H
