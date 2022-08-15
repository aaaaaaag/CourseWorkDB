#include "windows/cdk/MainMenuWindow.h"
#include "CdkCoordinator.h"
#include "AuthUserSingleton.h"
#include "CdkCoordinator.h"
#include "windows/cdk/CdkWindowsFactory.h"
#include "windows/cdk/SignUpWindow.h"
#include "windows/cdk/GuestTournamentWindow.h"

int main() {
    auto user= polytour::bl::AuthUserSingleton::getInstance();
    user->password = "mypass";
    user->nickname = "myuser";

    auto coordinator = std::make_shared<polytour::ui::CdkCoordinator>();
    //auto window = std::make_shared<polytour::ui::SignUpWindow>(coordinator);

//    polytour::transport::Tournament tournament;
//    tournament.id = 1;
//    tournament.status = "wait";
//    tournament.organizer_id = 1;
//    tournament.max_participants_num = 16;
//    tournament.cur_participants_num = 1;
//    tournament.name = "first";
//    auto window = std::make_shared<polytour::ui::cdk::GuestTournamentWindow>(coordinator, tournament);
//    window->init();
    auto windowsFactory = std::make_shared<polytour::ui::CdkWindowsFactory>(coordinator);
    coordinator->setFactory(windowsFactory);

    return 0;
}