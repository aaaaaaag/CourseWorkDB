//
// Created by denis on 7/23/22.
//

#include "transactions/TournamentTransactionFactory.h"
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
    auto* tournamentRepo = repoFactory.getTournamentRepository();
    auto* tournamentParticipantsRepo = repoFactory.getTournamentParticipantsRepository();

    auto updatedTournament = tournament;
    updatedTournament.cur_participants_num += 1;
    tournamentRepo->updateObj(tournament, updatedTournament);

    transport::TournamentParticipant tournamentParticipant;
    tournamentParticipant.tournament_id = tournament.id;
    tournamentParticipant.participant_id = _curUser.id;
    tournamentParticipantsRepo->addObj(tournamentParticipant);
}

void polytour::bl::transaction::TournamentTransactionFactory::leave(const polytour::transport::Tournament &tournament) {
    db::repository::RepositoryFactory repoFactory(_curUser);
    auto* tournamentRepo = repoFactory.getTournamentRepository();
    auto* tournamentParticipantsRepo = repoFactory.getTournamentParticipantsRepository();
    auto* matchRepo = repoFactory.getMatchRepository();

    auto updatedTournament = tournament;
    updatedTournament.cur_participants_num -= 1;
    tournamentRepo->updateObj(tournament, updatedTournament);

    auto participant = tournamentParticipantsRepo->findObj({
        .tournament_id_ = tournament.id,
        .participant_id_ = _curUser.id
    });
    if (participant.size() != 1)
        throw std::runtime_error("User doesn't take part in passed tournament");

    tournamentParticipantsRepo->deleteObj(participant[0]);

    transport::Match::search_t matchSearchObj1;
    matchSearchObj1.participant_1_id_ = _curUser.id;
    auto matchesWhereUserParticipant1 = matchRepo->findObj(matchSearchObj1);

    for (const auto& match: matchesWhereUserParticipant1) {
        auto updatedMatch = match;
        if (match.status == match.status_started ||
            match.status == match.status_wait_tribes) {
            updatedMatch.status = updatedMatch.status_finished;
            updatedMatch.loser_id = updatedMatch.participant_1_id;
            updatedMatch.winner_id = updatedMatch.participant_2_id;
        }
        else if (match.status == match.status_wait_participants) {
            updatedMatch.loser_id = updatedMatch.participant_1_id;
        }
        matchRepo->updateObj(match, updatedMatch);
    }

    transport::Match::search_t matchSearchObj2;
    matchSearchObj2.participant_2_id_ = _curUser.id;
    auto matchesWhereUserParticipant2 = matchRepo->findObj(matchSearchObj2);

    for (const auto& match: matchesWhereUserParticipant2) {
        auto updatedMatch = match;
        if (match.status == match.status_started ||
            match.status == match.status_wait_tribes) {
            updatedMatch.status = updatedMatch.status_finished;
            updatedMatch.loser_id = updatedMatch.participant_2_id;
            updatedMatch.winner_id = updatedMatch.participant_1_id;
        }
        else if (match.status == match.status_wait_participants) {
            updatedMatch.loser_id = updatedMatch.participant_2_id;
        }
        matchRepo->updateObj(match, updatedMatch);
    }
}

polytour::bl::transaction::TournamentTransactionFactory::TournamentTransactionFactory(
        polytour::transport::User curUser): _curUser(std::move(curUser)) {}
