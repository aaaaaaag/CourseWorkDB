//
// Created by denis on 02.08.2022.
//

#ifndef COURSEWORKDB_IWINDOWSFACTORY_H
#define COURSEWORKDB_IWINDOWSFACTORY_H

#include "IWindow.h"
#include <memory>

namespace polytour::ui {
    class IWindowsFactory {
    public:

        virtual ~IWindowsFactory() = default;

        virtual std::unique_ptr<IWindow> createAuthorizationWindow() = 0;

        virtual std::unique_ptr<IWindow> createMainMenuWindow() = 0;

        virtual std::unique_ptr<IWindow> createTournamentWindow() = 0;

        virtual std::unique_ptr<IWindow> createUserInfoWindow() = 0;
    };
}


#endif //COURSEWORKDB_IWINDOWSFACTORY_H
