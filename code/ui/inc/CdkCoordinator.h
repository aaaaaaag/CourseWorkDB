//
// Created by denis on 03.08.2022.
//

#ifndef COURSEWORKDB_CDKCOORDINATOR_H
#define COURSEWORKDB_CDKCOORDINATOR_H

#include "ICoordinator.h"

namespace polytour::ui {
    class CdkCoordinator: public ICoordinator{
    public:
        CdkCoordinator();

        void authorize(const std::string &nick, const std::string &pass) override;

        bl::facade::IMainFacade &getMainAPI() override;

    private:

        std::unique_ptr<bl::facade::IMainFacade> _pMainFacade;

    };
}


#endif //COURSEWORKDB_CDKCOORDINATOR_H
