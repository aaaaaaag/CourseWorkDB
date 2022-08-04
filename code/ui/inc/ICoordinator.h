//
// Created by denis on 03.08.2022.
//

#ifndef COURSEWORKDB_ICOORDINATOR_H
#define COURSEWORKDB_ICOORDINATOR_H

#include <string>
#include "facade/IMainFacade.h"

namespace polytour::ui {
    class ICoordinator {
    public:

        virtual ~ICoordinator() = default;

        virtual void authorize(const std::string& nick, const std::string& pass) = 0;

        virtual bl::IMainFacade& getMainAPI() = 0;

    };
}

#endif //COURSEWORKDB_ICOORDINATOR_H
