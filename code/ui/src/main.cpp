/* $Id: entry_ex.c,v 1.17 2016/12/04 15:22:16 tom Exp $ */

#include <cdk/cdk.h>
#include <string>
#include "AuthorizationWindow.h"

int main() {
    auto window = std::make_unique<polytour::ui::cdk::AuthorizationWindow>();
}