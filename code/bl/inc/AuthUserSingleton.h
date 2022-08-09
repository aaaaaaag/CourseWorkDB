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
    private:

        AuthUserSingleton() = default;

        AuthUserSingleton(const AuthUserSingleton&) = default;
        AuthUserSingleton& operator = (AuthUserSingleton &) = default;

        //static std::unique_ptr<transport::User> _pInstance;

    public:

        static void authorize(const std::string& nick,
                              const std::string& pass) {
            //_pInstance = std::make_unique<transport::User>();
            getInstance()->nickname = nick;
            getInstance()->password = pass;
            //_pInstance->nickname = nick;
            //_pInstance->password = pass;
        };

        static transport::User* getInstance() {
            static std::unique_ptr<transport::User> _pInstance = std::make_unique<transport::User>();

            return _pInstance.get();
            //return _pInstance.get();
        };
    };
}

#endif //COURSEWORKDB_AUTHUSERSINGLETON_H
