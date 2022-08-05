//
// Created by denis on 04.08.2022.
//

#include "facade/MatchFacade.h"
#include "transactions/MatchTransactionFactory.h"
#include "AuthUserSingleton.h"

void polytour::bl::facade::MatchFacade::create(const polytour::transport::Match &match) {
    _pTransactionFactory->create(match);
}

void polytour::bl::facade::MatchFacade::erase(const polytour::transport::Match &match) {
    _pTransactionFactory->erase(match);
}

std::vector<polytour::transport::Match>
polytour::bl::facade::MatchFacade::getMatches(const polytour::transport::Match::search_t &search) {
    return _pTransactionFactory->getMatches(search);
}

polytour::bl::facade::MatchFacade::MatchFacade():
_pTransactionFactory(std::make_unique<transaction::MatchTransactionFactory>(*AuthUserSingleton::getInstance())){}
