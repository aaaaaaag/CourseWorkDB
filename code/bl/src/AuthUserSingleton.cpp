//
// Created by denis on 03.08.2022.
//

#include "AuthUserSingleton.h"

polytour::transport::User *polytour::bl::AuthUserSingleton::getInstance() {
    return _pInstance.get();
}
