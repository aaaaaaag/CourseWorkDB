//
// Created by denis on 03.08.2022.
//

#include "CdkCoordinator.h"
#include "facade/MainFacade.h"

void polytour::ui::CdkCoordinator::authorize(const std::string &nick, const std::string &pass) {

}

polytour::bl::facade::IMainFacade &polytour::ui::CdkCoordinator::getMainAPI() {
    return *_pMainFacade;
}

polytour::ui::CdkCoordinator::CdkCoordinator():
_pMainFacade(std::make_unique<bl::facade::MainFacade>()){}