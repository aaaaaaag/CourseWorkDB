//
// Created by denis on 03.08.2022.
//

#ifndef COURSEWORKDB_AUTHUSERSINGLETON_H
#define COURSEWORKDB_AUTHUSERSINGLETON_H

#include "User.h"
#include <memory>
#include <string>

namespace polytour::bl {
    class AuthUserSingleton {
    public:

        static void authorize(const std::string& nick,
                              const std::string& pass);

        static transport::User* getInstance();

    private:

        AuthUserSingleton() = default;

        AuthUserSingleton(const AuthUserSingleton&) = default;
        AuthUserSingleton& operator = (AuthUserSingleton &) = default;

        static std::unique_ptr<transport::User> _pInstance;
    };
}

#endif //COURSEWORKDB_AUTHUSERSINGLETON_H
