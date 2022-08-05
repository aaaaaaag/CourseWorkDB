//
// Created by denis on 04.08.2022.
//

#include "transactions/MatchTransactionFactory.h"
#include "repositories/RepositoryFactory.h"
#include <utility>
#include "AuthUserSingleton.h"

void polytour::bl::transaction::MatchTransactionFactory::create(const polytour::transport::Match &match) {
    db::repository::RepositoryFactory repoFactory(_pRole);
    repoFactory.getMatchRepository()->addObj(match);
}

void polytour::bl::transaction::MatchTransactionFactory::erase(const polytour::transport::Match &match) {
    db::repository::RepositoryFactory repoFactory(_pRole);
    repoFactory.getMatchRepository()->deleteObj(match);
}

std::vector<polytour::transport::Match>
polytour::bl::transaction::MatchTransactionFactory::getMatches(const polytour::transport::Match::search_t &search) {
    db::repository::RepositoryFactory repoFactory(_pRole);
    return repoFactory.getMatchRepository()->findObj(search);
}

void polytour::bl::transaction::MatchTransactionFactory::updateMatch(const polytour::transport::Match &curMatch,
                                                                     const polytour::transport::Match &newMatch) {
    db::repository::RepositoryFactory repoFactory(_pRole);
    repoFactory.getMatchRepository()->updateObj(curMatch, newMatch);
}

polytour::bl::transaction::MatchTransactionFactory::MatchTransactionFactory(std::shared_ptr<db::repository::roles::IRole> role):
_pRole(std::move(role)),
_curUser(*AuthUserSingleton::getInstance()){}
