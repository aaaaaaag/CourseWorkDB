//
// Created by denis on 03.08.2022.
//

#ifndef COURSEWORKDB_IUSERFACADE_H
#define COURSEWORKDB_IUSERFACADE_H

#include <vector>
#include <string>
#include "User.h"

namespace polytour::bl::facade {
    class IUserFacade {
    public:

        virtual ~IUserFacade() = default;

        virtual void auth(const std::string& nick, const std::string& pass) = 0;

        virtual std::vector<transport::User> getUsers(transport::User::search_t search) = 0;

        virtual void deleteUser(const transport::User& user) = 0;

        virtual void regNewUser(const transport::User& user) = 0;
    };
}

#endif //COURSEWORKDB_IUSERFACADE_H
