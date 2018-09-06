#ifndef RPNEWS_ERRORMESSAGEMAKER_H
#define RPNEWS_ERRORMESSAGEMAKER_H

#include <string>

class ErrorMessageMaker
{
public:
    ErrorMessageMaker() = default;
    ~ErrorMessageMaker() = default;
    static std::string getErrorMessage(const std::string& methodName);
};

#endif //RPNEWS_ERRORMESSAGEMAKER_H
