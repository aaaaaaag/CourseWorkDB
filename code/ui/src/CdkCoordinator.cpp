//
// Created by denis on 03.08.2022.
//

#include "CdkCoordinator.h"

#include <utility>
#include "facade/MainFacade.h"

std::optional<polytour::bl::ErrorObj>
polytour::ui::CdkCoordinator::authorize(const std::string &nick, const std::string &pass) {
    _pMainFacade->userAPI()->auth(nick, pass);
    auto error = _pMainFacade->userAPI()->getError();
    if (error)
        return error;
    //_pCurrentWindow->destroy();
    _pCurrentWindow = _pWindowsFactory->createMainMenuWindow();
    return std::nullopt;
}

polytour::bl::facade::IMainFacade &polytour::ui::CdkCoordinator::getMainAPI() {
    return *_pMainFacade;
}

void polytour::ui::CdkCoordinator::setFactory(std::shared_ptr<IWindowsFactory> factory) {
    _pWindowsFactory = std::move(factory);
    _pCurrentWindow = _pWindowsFactory->createAuthorizationWindow();
}

polytour::ui::CdkCoordinator::CdkCoordinator():
_pWindowsFactory(nullptr),
_pMainFacade(std::make_unique<bl::facade::MainFacade>()){
}

std::optional<polytour::bl::ErrorObj> polytour::ui::CdkCoordinator::signUp(polytour::transport::User user) {
    _pMainFacade->userAPI()->regNewUser(user);
    if (_pMainFacade->userAPI()->isError())
        return _pMainFacade->userAPI()->getError();
    toSignIn();
}

std::optional<polytour::bl::ErrorObj> polytour::ui::CdkCoordinator::toSignIn() {
    //_pCurrentWindow->destroy();
    _pCurrentWindow = _pWindowsFactory->createAuthorizationWindow();
    return std::nullopt;
}

std::optional<polytour::bl::ErrorObj> polytour::ui::CdkCoordinator::toSignUp() {
    //_pCurrentWindow->destroy();
    _pCurrentWindow = _pWindowsFactory->createSignUpWindow();
    return std::nullopt;
}
