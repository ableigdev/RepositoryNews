#include "ErrorMessageMaker.h"
#include "git2.h"

std::string ErrorMessageMaker::getErrorMessage(const std::string& methodName)
{
    return std::move(std::string("Problem with " + methodName + ", error message : '" + std::string(giterr_last()->message) + "'"));
}