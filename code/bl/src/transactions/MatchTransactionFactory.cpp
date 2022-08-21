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

void polytour::bl::transaction::MatchTransactionFactory::finish(const polytour::transport::Match &match, const transport::User& winner) {
    db::repository::RepositoryFactory repoFactory(_pRole);
    auto matchRepo = repoFactory.getMatchRepository();
    auto updatedMatch = match;
    updatedMatch.status = transport::Match::status_finished();
    if (updatedMatch.participant_1_id.getValue() == winner.id) {
        updatedMatch.winner_id = winner.id;
        updatedMatch.loser_id = updatedMatch.participant_2_id;
    } else if (updatedMatch.participant_2_id.getValue() == winner.id) {
        updatedMatch.winner_id = winner.id;
        updatedMatch.loser_id = updatedMatch.participant_1_id;
    } else {
        throw polytour::CriticalError("Match take invalid user for finish operation");
    }
    matchRepo->updateObj(match, updatedMatch);

    // Search for matches in the next tour
    auto matchTour = match.tour;
    auto nextTourMatches = matchRepo->findObj({
        .tournament_id_ = match.tournament_id,
        .tour_ = matchTour + 1});
    if (!nextTourMatches.empty()) {
        for(const auto& nextMatch: nextTourMatches) {
            auto updatedNextMatch = nextMatch;
            if (nextMatch.participant_1_id.isNull()) {
                updatedNextMatch.participant_1_id = winner.id;
            } else if (nextMatch.participant_2_id.isNull()) {
                updatedNextMatch.participant_2_id = winner.id;
                updatedNextMatch.status = transport::Match::status_wait_tribes();
            } else {
                continue;
            }
            matchRepo->updateObj(nextMatch, updatedNextMatch);
            break;
        }
    } else {
        auto tournamentRepo = repoFactory.getTournamentRepository();
        auto tournament = tournamentRepo->findObj({.id_ = match.tournament_id})[0];
        auto updatedTournament = tournament;
        updatedTournament.status = transport::Tournament::status_finished();
        tournamentRepo->updateObj(tournament, updatedTournament);
    }
}

polytour::bl::transaction::MatchTransactionFactory::MatchTransactionFactory(std::shared_ptr<db::repository::roles::IRole> role):
_pRole(std::move(role)),
_curUser(*AuthUserSingleton::getInstance()){}
