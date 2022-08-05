#include "windows/MainMenuWindow.h"
#include "CdkCoordinator.h"
#include "AuthUserSingleton.h"

int main() {
    auto user= polytour::bl::AuthUserSingleton::getInstance();
    user->password = "mypass";
    user->nickname = "myuser";

    auto coordinator = std::make_shared<polytour::ui::CdkCoordinator>();
    auto mainMenu = std::make_shared<polytour::ui::MainMenuWindow>(coordinator);

    return 0;
}
