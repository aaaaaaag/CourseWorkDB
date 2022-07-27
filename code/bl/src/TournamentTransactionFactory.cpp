//
// Created by denis on 7/23/22.
//

#include "TournamentTransactionFactory.h"
#include <utility>
#include "repositories/RepositoryFactory.h"

void
polytour::bl::transaction::TournamentTransactionFactory::create(const polytour::transport::Tournament &tournament) {
    db::repository::RepositoryFactory repoFactory(_curUser);
    repoFactory.getTournamentRepository()->addObj(tournament);
}

void polytour::bl::transaction::TournamentTransactionFactory::erase(const polytour::transport::Tournament &tournament) {
    db::repository::RepositoryFactory repoFactory(_curUser);
    auto* tournamentRepo = repoFactory.getTournamentRepository();
    auto* matchRepo = repoFactory.getMatchRepository();
    auto* tournamentParticipantsRepo = repoFactory.getTournamentParticipantsRepository();
    auto tournamentMatches = matchRepo->findObj({.tournament_id_ = tournament.id});
    for (const auto& match: tournamentMatches)
        matchRepo->deleteObj(match);
    auto tournamentParticipants = tournamentParticipantsRepo->findObj({.tournament_id_ = tournament.id});
    for (const auto& participant: tournamentParticipants)
        tournamentParticipantsRepo->deleteObj(participant);
    tournamentRepo->deleteObj(tournament);
}

void polytour::bl::transaction::TournamentTransactionFactory::join(const polytour::transport::Tournament &tournament) {
    if ((tournament.cur_participants_num == tournament.max_participants_num) and
    (tournament.status != tournament.status_wait_for_participants))
        return;

    db::repository::RepositoryFactory repoFactory(_curUser);
    auto updatedTournament = tournament;
    updatedTournament.cur_participants_num += 1;

    auto* tournamentRepo = repoFactory.getTournamentRepository();
    auto* tournamentParticipantsRepo = repoFactory.getTournamentParticipantsRepository();

    tournamentRepo->updateObj(tournament, updatedTournament);
    transport::TournamentParticipants tournamentParticipant;
    tournamentParticipant.id
    tournamentParticipantsRepo->addObj()


}

void polytour::bl::transaction::TournamentTransactionFactory::leave(const polytour::transport::Tournament &tournament) {

}

polytour::bl::transaction::TournamentTransactionFactory::TournamentTransactionFactory(
        polytour::transport::User curUser): _curUser(std::move(curUser)) {}
