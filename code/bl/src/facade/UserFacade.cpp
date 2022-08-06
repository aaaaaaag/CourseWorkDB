//
// Created by denis on 04.08.2022.
//

#include "facade/UserFacade.h"
#include "AuthUserSingleton.h"
#include "transactions/UserTransactionFactory.h"
#include "repositories/roles/GuestRole.h"
#include "NotCriticalError.h"

void polytour::bl::facade::UserFacade::auth(const std::string &nick, const std::string &pass) {
    processError([this, pass, nick]() {
        auto users = _pTransactionFactory->searchUsers({.password_ = pass, .nickname_ = nick});
        if (users.size() != 1)
            throw polytour::NotCriticalError("Failed authorization");

        polytour::bl::AuthUserSingleton::authorize(nick, pass);
    });
}

std::vector<polytour::transport::User> polytour::bl::facade::UserFacade::getUsers(polytour::transport::User::search_t search) {
    processError([this, search]() {
        return _pTransactionFactory->searchUsers(search);
    });
}

void polytour::bl::facade::UserFacade::deleteUser(const polytour::transport::User &user) {
    processError([this, user]() {
        _pTransactionFactory->deleteUser(user);
    });
}

void polytour::bl::facade::UserFacade::regNewUser(const polytour::transport::User &user) {
    processError([this, user]() {
        if (user.nickname.empty())
            throw polytour::NotCriticalError("Nickname field doesn't passed");
        auto users = _pTransactionFactory->searchUsers({.nickname_ = user.nickname});
        if (!users.empty())
            throw polytour::NotCriticalError("Nickname is already in use. Pass another");
        if (user.password.empty())
            throw polytour::NotCriticalError("Password field doesn't passed");
        if (user.name.empty())
            throw polytour::NotCriticalError("Name field doesn't passed");
        if (user.email.empty())
            throw polytour::NotCriticalError("Email field doesn't passed");
        _pTransactionFactory->addUser(user);
    });
}

polytour::bl::facade::UserFacade::UserFacade():
_pTransactionFactory(std::make_unique<transaction::UserTransactionFactory>(
        std::make_shared<db::repository::roles::GuestRole>())){}
