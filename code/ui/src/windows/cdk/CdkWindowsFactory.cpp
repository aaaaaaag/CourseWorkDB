//
// Created by denis on 05.08.2022.
//

#include "windows/cdk/CdkWindowsFactory.h"

#include <utility>
#include "windows/cdk/AuthorizationWindow.h"
#include "windows/cdk/MainMenuWindow.h"
#include "windows/cdk/SignUpWindow.h"

std::unique_ptr<polytour::ui::IWindow> polytour::ui::CdkWindowsFactory::createAuthorizationWindow() {
    return std::make_unique<cdk::AuthorizationWindow>(_pCoordinator.lock());
}

std::unique_ptr<polytour::ui::IWindow> polytour::ui::CdkWindowsFactory::createMainMenuWindow() {
    return std::make_unique<MainMenuWindow>(_pCoordinator.lock());
}

std::unique_ptr<polytour::ui::IWindow> polytour::ui::CdkWindowsFactory::createTournamentWindow() {
    return nullptr;
}

std::unique_ptr<polytour::ui::IWindow> polytour::ui::CdkWindowsFactory::createUserInfoWindow() {
    return nullptr;
}

std::unique_ptr<polytour::ui::IWindow> polytour::ui::CdkWindowsFactory::createSignUpWindow() {
    return std::make_unique<cdk::SignUpWindow>(_pCoordinator.lock());
}

polytour::ui::CdkWindowsFactory::CdkWindowsFactory(const std::shared_ptr<ICoordinator>& coordinator):
_pCoordinator(coordinator){

}
