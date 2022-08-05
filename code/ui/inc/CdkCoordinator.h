//
// Created by denis on 03.08.2022.
//

#ifndef COURSEWORKDB_CDKCOORDINATOR_H
#define COURSEWORKDB_CDKCOORDINATOR_H

#include "ICoordinator.h"
#include "windows/IWindowsFactory.h"
#include "memory"

namespace polytour::ui {
    class CdkCoordinator: public ICoordinator{
    public:
        explicit CdkCoordinator();

        void setFactory(std::shared_ptr<IWindowsFactory> factory);

        std::optional<bl::ErrorObj> authorize(const std::string &nick, const std::string &pass) override;

        bl::facade::IMainFacade &getMainAPI() override;

    private:

        std::unique_ptr<IWindow> _pCurrentWindow;

        std::shared_ptr<IWindowsFactory> _pWindowsFactory;
        std::unique_ptr<bl::facade::IMainFacade> _pMainFacade;

    };
}


#endif //COURSEWORKDB_CDKCOORDINATOR_H
