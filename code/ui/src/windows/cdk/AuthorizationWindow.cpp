//
// Created by denis on 02.08.2022.
//

#include "windows/cdk/AuthorizationWindow.h"
#include "cdk/cdk.h"
#include <string>
#include <functional>
#include <utility>

static BINDFN_PROTO (activateEntry);
static BINDFN_PROTO (activateButton);
static BINDFN_PROTO (authorize);
static BINDFN_PROTO (cancel);

typedef struct UserData {
    SScreen* cdk_screen;
    std::weak_ptr<polytour::ui::ICoordinator> coordinator;
    const char* nickname;
    const char* password;
} UserData;

class polytour::ui::cdk::AuthorizationWindow::Impl {
public:

    explicit Impl(std::shared_ptr<ICoordinator> coordinator): _pCoordinator(std::move(coordinator)) {
        cdkScreen = initCDKScreen(nullptr);
        initCDKColor ();

        // Init nickname entry
        nick_entry = newCDKEntry (cdkScreen, CENTER, CENTER, "", "</U/6>Nickname: <!U!6>", A_NORMAL, '_', vMIXED,
                                        40, 256, 256, TRUE, FALSE);
        setCDKEntryLLChar(nick_entry, ACS_LTEE);
        setCDKEntryLRChar(nick_entry, ACS_RTEE);

        // Init password entry
        pass_entry = newCDKEntry (cdkScreen, getbegx(nick_entry->win),
                                        getbegy(nick_entry->win) + nick_entry->boxHeight - 1,
                                        "", "</U/6>Password: <!U!6>", A_NORMAL, '_', vMIXED, 40, 0, 256, TRUE, FALSE);
        setCDKEntryULChar(pass_entry, ACS_LTEE);
        setCDKEntryURChar(pass_entry, ACS_RTEE);
        setCDKEntryLLChar(pass_entry, ACS_LTEE);
        setCDKEntryLRChar(pass_entry, ACS_RTEE);

        // Init authorization button
        auto width = nick_entry->boxWidth;
        auto entryXPos = getbegx(nick_entry->win);
        std::string nameAuthButton = "<C>" + std::string(width / 4 - 4, ' ') + "Log in" + std::string(width / 4 - 3, ' ');
        authorizationButton = newCDKButton(cdkScreen, entryXPos,
                                          getbegy (pass_entry->win) + pass_entry->boxHeight - 1,
                                           nameAuthButton.data(), nullptr, TRUE, FALSE);
        setCDKButtonboxULChar (authorizationButton, ACS_LTEE);
        setCDKButtonboxURChar (authorizationButton, ACS_TTEE);
        setCDKButtonboxLRChar (authorizationButton, ACS_LRCORNER);

        // Init cancel button
        std::string name = "<C>" + std::string(width / 4 - 4, ' ') + "Cancel" + std::string(width / 4 - 4, ' ');
        cancelButton = newCDKButton(cdkScreen, entryXPos + width / 2,
                                           getbegy (pass_entry->win) + pass_entry->boxHeight - 1,
                                           name.data(), nullptr, TRUE, FALSE);
        setCDKButtonboxULChar (cancelButton, ACS_TTEE);
        setCDKButtonboxURChar (cancelButton, ACS_RTEE);
        setCDKButtonboxLLChar (cancelButton, ACS_LLCORNER);

        // Init logo
        const char* label_text[] = {"               </B/K/5> Polytour <!B!K!5>                "};
        logo = newCDKLabel(cdkScreen, CENTER,
                                 getbegy(nick_entry->win) - nick_entry->boxHeight - 1,
                                 (CDK_CSTRING2)label_text, 1, TRUE, TRUE);

        // Initialization of utility struct
        UserData userData {
                .cdk_screen = cdkScreen,
                .coordinator = _pCoordinator,
                .nickname = nick_entry->info,
                .password = pass_entry->info
        };

        // Widgets binding section
        bindCDKObject (vENTRY, nick_entry, KEY_TAB, activateEntry, pass_entry);
        bindCDKObject (vENTRY, nick_entry, KEY_ENTER, activateEntry, pass_entry);
        bindCDKObject (vENTRY, pass_entry, KEY_TAB, activateButton, authorizationButton);
        bindCDKObject (vENTRY, pass_entry, KEY_ENTER, activateButton, authorizationButton);
        bindCDKObject (vBUTTON, authorizationButton, KEY_TAB, activateButton, cancelButton);
        bindCDKObject (vBUTTON, cancelButton, KEY_TAB, activateEntry, nick_entry);
        std::function<void()> cancelFunc = [this](){destroy();};
        bindCDKObject (vBUTTON, cancelButton, KEY_ENTER, cancel, &cancelFunc);
        bindCDKObject(vBUTTON, authorizationButton, KEY_ENTER, authorize, &userData);

        refreshCDKScreen (cdkScreen);
        (void)activateCDKEntry (nick_entry, nullptr);
    }

    ~Impl() {
        destroy();
    }

    void destroy() {
        if (isDestroyed)
            return;
        /* Clean up and exit. */

        destroyCDKButton(cancelButton);
        destroyCDKButton(authorizationButton);
        destroyCDKLabel(logo);
        destroyCDKEntry (pass_entry);
        destroyCDKEntry (nick_entry);
        destroyCDKScreen (cdkScreen);
        endCDK ();
        isDestroyed = true;
    };

    bool isDestroyed = false;
    std::weak_ptr<ICoordinator> _pCoordinator;
    SEntry* nick_entry;
    SEntry* pass_entry;
    SButton* authorizationButton;
    SButton* cancelButton;
    SLabel* logo;
    SScreen* cdkScreen;
};

polytour::ui::cdk::AuthorizationWindow::AuthorizationWindow(const std::shared_ptr<ICoordinator>& coordinator):
_pImpl(std::make_unique<Impl>(coordinator)){
}

void polytour::ui::cdk::AuthorizationWindow::destroy() {
    _pImpl->destroy();
}

polytour::ui::cdk::AuthorizationWindow::~AuthorizationWindow() = default;

static int deactivateObj(EObjectType cdktype GCC_UNUSED, void *object GCC_UNUSED) {
    chtype esc = KEY_ESC;
    if (cdktype == vBUTTON)
        (void) activateCDKButton((CDKBUTTON*)object, &esc);
    else if (cdktype == vENTRY)
        (void) activateCDKEntry((CDKENTRY*) object, &esc);
    else return (FALSE);
    return (TRUE);
}

static int activateEntry (EObjectType cdktype GCC_UNUSED, void *object GCC_UNUSED, void *clientData, chtype key)
{
    if (!deactivateObj(cdktype, object)) return (FALSE);

    auto *entry = (CDKENTRY *)clientData;
    (void) activateCDKEntry(entry, nullptr);
    return (TRUE);
}

static int activateButton (EObjectType cdktype GCC_UNUSED, void *object GCC_UNUSED, void *clientData, chtype key)
{
    if (!deactivateObj(cdktype, object)) return (FALSE);

    auto *buttonbox = (CDKBUTTON *)clientData;
    (void)activateCDKButton(buttonbox, nullptr);
    return (TRUE);
}

static int cancel (EObjectType cdktype GCC_UNUSED, void *object GCC_UNUSED, void *clientData, chtype key)
{
    chtype esc = KEY_ESC;
    (void) activateCDKButton((CDKBUTTON*)object, &esc);
    auto cancelFunc = (std::function<void()>*)clientData;
    (*cancelFunc)();
    return (TRUE);
}

static int authorize (EObjectType cdktype GCC_UNUSED, void *object GCC_UNUSED, void *clientData, chtype key)
{
    auto* userData = (UserData*)clientData;

    auto coordinator = userData->coordinator;
    auto err = coordinator.lock()->authorize(userData->nickname, userData->password);
    if (!err)
        return (FALSE);


    const char *mesg[10];
    char nick[256];
    sprintf (nick, "<C>Nickname: (%.*s)", (int)(sizeof (nick) - 10), userData->nickname);
    char pass[256];
    sprintf (pass, "<C>Password: (%.*s)", (int)(sizeof (pass) - 10), userData->password);
    mesg[0] = "<C>You typed the following: ";
    mesg[1] = nick;
    mesg[2] = pass;
    mesg[3] = "";
    mesg[4] = "<C>Press any key to continue.";
    popupLabel (userData->cdk_screen, (CDK_CSTRING2) mesg, 4);
    return (TRUE);
}

