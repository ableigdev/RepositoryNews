#include <regex>
#include <stdexcept>
#include "GitRepositoryTypeImpl.h"

GitRepositoryTypeImpl::GitRepositoryTypeImpl(const std::string &url, const secure_string& user, const secure_string& pass)
{
    auto name = getRepositoryFolderName(url);
    if (name.empty())
    {
        throw std::logic_error("Invalid url");
    }

    m_Repository.create(".configs/" + name);
    m_Remote.create(m_Repository, url);

}

std::string GitRepositoryTypeImpl::getRepositoryFolderName(const std::string& url)
{
    std::regex regexValue(R"(\/([\w]+)\.[\w]+$)");
    std::cmatch result;
    std::regex_match(url.data(), result, regexValue);
    return result.str();
}