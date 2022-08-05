//
// Created by denis on 05.08.2022.
//

#ifndef COURSEWORKDB_CDKWINDOWSFACTORY_H
#define COURSEWORKDB_CDKWINDOWSFACTORY_H

#include "windows/IWindowsFactory.h"
#include "ICoordinator.h"

namespace polytour::ui {
    class CdkWindowsFactory: public IWindowsFactory{
    public:

        explicit CdkWindowsFactory(const std::shared_ptr<ICoordinator>& coordinator);

        std::unique_ptr<IWindow> createAuthorizationWindow() override;

        std::unique_ptr<IWindow> createMainMenuWindow() override;

        std::unique_ptr<IWindow> createTournamentWindow() override;

        std::unique_ptr<IWindow> createUserInfoWindow() override;

    private:

        std::weak_ptr<ICoordinator> _pCoordinator;

    };
}


#endif //COURSEWORKDB_CDKWINDOWSFACTORY_H
