//
// Created by denis on 04.08.2022.
//

#include "facade/MainFacade.h"
#include "facade/TournamentFacade.h"
#include "facade/UserFacade.h"
#include "facade/MatchFacade.h"

std::shared_ptr<polytour::bl::facade::IUserFacade> polytour::bl::facade::MainFacade::userAPI() {
    return _pUserFacade;
}

std::shared_ptr<polytour::bl::facade::ITournamentFacade> polytour::bl::facade::MainFacade::tournamentAPI() {
    return _pTournamentFacade;
}

std::shared_ptr<polytour::bl::facade::IMatchFacade> polytour::bl::facade::MainFacade::matchFacade() {
    return _pMatchFacade;
}

polytour::bl::facade::MainFacade::MainFacade():
_pUserFacade(std::make_shared<UserFacade>()),
_pTournamentFacade(std::make_shared<TournamentFacade>()),
_pMatchFacade(std::make_shared<MatchFacade>()){
}
