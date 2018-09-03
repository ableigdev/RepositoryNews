#ifndef RPNEWS_RPNEWS_TYPES_H
#define RPNEWS_RPNEWS_TYPES_H

#include "SecureAllocator.h"
#include <string>

typedef std::basic_string<char, std::char_traits<char>, secure::SecureAllocator<char>> secure_string;

struct commit
{
    std::string author;
    std::string message;
};

#endif //RPNEWS_RPNEWS_TYPES_H
