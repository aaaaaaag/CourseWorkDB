//
// Created by denis on 04.08.2022.
//

#include "facade/UserFacade.h"
#include "AuthUserSingleton.h"
#include "transactions/UserTransactionFactory.h"

void polytour::bl::facade::UserFacade::auth(const std::string &nick, const std::string &pass) {
    polytour::bl::AuthUserSingleton::authorize(nick, pass);
}

std::vector<polytour::transport::User> polytour::bl::facade::UserFacade::getUsers(polytour::transport::User::search_t search) {
    return _pTransactionFactory->searchUsers(search);
}

void polytour::bl::facade::UserFacade::deleteUser(const polytour::transport::User &user) {
    _pTransactionFactory->deleteUser(user);
}

void polytour::bl::facade::UserFacade::regNewUser(const polytour::transport::User &user) {
    _pTransactionFactory->addUser(user);
}

polytour::bl::facade::UserFacade::UserFacade():
_pTransactionFactory(std::make_unique<transaction::UserTransactionFactory>(*AuthUserSingleton::getInstance())) {

}
