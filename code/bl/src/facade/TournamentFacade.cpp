//
// Created by denis on 04.08.2022.
//

#include "facade/TournamentFacade.h"
#include "transactions/TournamentTransactionFactory.h"
#include "AuthUserSingleton.h"
#include "repositories/roles/GuestRole.h"


void polytour::bl::facade::TournamentFacade::create(const polytour::transport::Tournament &tournament) {
    _pTransactionFactory->create(tournament);
}

void polytour::bl::facade::TournamentFacade::remove(const polytour::transport::Tournament &tournament) {
    _pTransactionFactory->erase(tournament);
}

std::vector<polytour::transport::Tournament>
polytour::bl::facade::TournamentFacade::getTournaments(const polytour::transport::Tournament::search_t &search) {
    return _pTransactionFactory->search(search);
}

polytour::bl::facade::TournamentFacade::TournamentFacade():
_pTransactionFactory(std::make_unique<transaction::TournamentTransactionFactory>(
                        std::make_shared<db::repository::roles::GuestRole>())){}
