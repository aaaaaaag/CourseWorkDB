//
// Created by denis on 02.08.2022.
//

#ifndef COURSEWORKDB_AUTHORIZATIONWINDOW_H
#define COURSEWORKDB_AUTHORIZATIONWINDOW_H

#include "IAuthorizationWindow.h"
#include <memory>

namespace polytour::ui::cdk {
    class AuthorizationWindow : public IAuthorizationWindow {
    public:

        AuthorizationWindow();

        ~AuthorizationWindow() override;

    private:

        class Impl;
        std::unique_ptr<Impl> _pImpl;

    };
}


#endif //COURSEWORKDB_AUTHORIZATIONWINDOW_H
