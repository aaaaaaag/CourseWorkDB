//
// Created by denis on 04.08.2022.
//

#include "transactions/MatchTransactionFactory.h"
#include "repositories/RepositoryFactory.h"
#include <utility>

void polytour::bl::transaction::MatchTransactionFactory::create(const polytour::transport::Match &match) {
    db::repository::RepositoryFactory repoFactory(_curUser);
    repoFactory.getMatchRepository()->addObj(match);
}

void polytour::bl::transaction::MatchTransactionFactory::erase(const polytour::transport::Match &match) {
    db::repository::RepositoryFactory repoFactory(_curUser);
    repoFactory.getMatchRepository()->deleteObj(match);
}

std::vector<polytour::transport::Match>
polytour::bl::transaction::MatchTransactionFactory::getMatches(const polytour::transport::Match::search_t &search) {
    db::repository::RepositoryFactory repoFactory(_curUser);
    return repoFactory.getMatchRepository()->findObj(search);
}

void polytour::bl::transaction::MatchTransactionFactory::updateMatch(const polytour::transport::Match &curMatch,
                                                                     const polytour::transport::Match &newMatch) {
    db::repository::RepositoryFactory repoFactory(_curUser);
    repoFactory.getMatchRepository()->updateObj(curMatch, newMatch);
}

polytour::bl::transaction::MatchTransactionFactory::MatchTransactionFactory(polytour::transport::User curUser):
        _curUser(std::move(curUser)){}
