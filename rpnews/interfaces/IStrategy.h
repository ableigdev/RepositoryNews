#ifndef RPNEWS_ISTRATEGY_H
#define RPNEWS_ISTRATEGY_H

#include <string>
#include "wrappers/GitRemoteWrapper.h"
#include "wrappers/RepositoryWrapper.h"

namespace interfaces
{
//    template <typename StringType = std::string,
//            typename RepositoryType = git_wrapper::RepositoryWrapper,
//            typename RemoteType = git_wrapper::GitRemoteWrapper>
    class IStrategy
    {
    public:
        IStrategy() = default;
        virtual ~IStrategy() = default;
        virtual void raiseRepository(std::string* name, const std::string& url, git_wrapper::RepositoryWrapper* repository, git_wrapper::GitRemoteWrapper* remote) = 0;
//        virtual void raiseRepository(StringType&& str, RepositoryType&& repository, RemoteType&& remote) = 0;
//        StringType getString() const
//        {
//            return m_String;
//        }

//        RepositoryType getRepository() const
//        {
//            return m_Repository;
//        }

//        RemoteType getRemote() const
//        {
//            return m_Remote;
//        }

//    protected:
//        void setString(StringType&& str)
//        {
//            m_String = std::move(str);
//        }

//        void setRepository(RepositoryType&& repository)
//        {
//            m_Repository = std::move(repository);
//        }

//        void setRemote(RemoteType&& remote)
//        {
//            m_Remote = std::move(remote);
//        }

//    private:
//        StringType m_String;
//        RepositoryType m_Repository;
//        RemoteType m_Remote;
    };
}

#endif //RPNEWS_ISTRATEGY_H
