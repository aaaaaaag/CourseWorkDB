#include "windows/cdk/MainMenuWindow.h"
#include "CdkCoordinator.h"
#include "AuthUserSingleton.h"
#include "CdkCoordinator.h"
#include "windows/cdk/CdkWindowsFactory.h"
#include "windows/cdk/SignUpWindow.h"

int main() {
    auto user= polytour::bl::AuthUserSingleton::getInstance();
    user->password = "mypass";
    user->nickname = "myuser";

    auto coordinator = std::make_shared<polytour::ui::CdkCoordinator>();
    //auto window = std::make_shared<polytour::ui::SignUpWindow>(coordinator);

    auto windowsFactory = std::make_shared<polytour::ui::CdkWindowsFactory>(coordinator);
    coordinator->setFactory(windowsFactory);

    return 0;
}