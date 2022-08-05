//
// Created by denis on 04.08.2022.
//

#include "windows/MainMenuWindow.h"
#include <cdk/cdk.h>
#include <utility>
#include <vector>
#include <cstring>
#include <algorithm>
#include <cstdarg>  // For va_start, etc.
#include <memory>    // For std::unique_ptr
#include "Tournament.h"

static BINDFN_PROTO (activateScroll);

template<typename ... Args>
std::string string_format( const std::string& format, Args ... args )
{
    int size_s = std::snprintf( nullptr, 0, format.c_str(), args ... ) + 1; // Extra space for '\0'
    if( size_s <= 0 ){ throw std::runtime_error( "Error during formatting." ); }
    auto size = static_cast<size_t>( size_s );
    std::unique_ptr<char[]> buf( new char[ size ] );
    std::snprintf( buf.get(), size, format.c_str(), args ... );
    return std::string( buf.get(), buf.get() + size - 1 ); // We don't want the '\0' inside
}

class polytour::ui::MainMenuWindow::Impl {
public:

    explicit Impl(std::shared_ptr<ICoordinator> coordinator):
    _pCoordinator(std::move(coordinator)){
        cdkScreen = initCDKScreen(nullptr);
        initCDKColor ();
        initTournamentList();
    }

    ~Impl() {
        destroyCDKScroll(tourSelection);
        destroyCDKScreen (cdkScreen);
        endCDK ();
    }

private:

    void initTournamentList();
    std::vector<char*> getSelectionListElems();

    void initTournamentInfo();

    std::shared_ptr<ICoordinator> _pCoordinator;
    std::vector<transport::Tournament> _vActiveTournaments;


    SScreen *cdkScreen;
    SScroll* tourSelection{};
};





void polytour::ui::MainMenuWindow::Impl::initTournamentList() {

    int height;
    // HAHA here is fucking shit
    {
        const char *mesg[1];
        mesg[0] = "baba";
        auto first = newCDKLabel(cdkScreen, CENTER, CENTER, (CDK_CSTRING2)mesg, 1, TRUE, FALSE);
        auto second = newCDKLabel(cdkScreen, CENTER, BOTTOM, (CDK_CSTRING2)mesg, 1, TRUE, FALSE);
        height = second->ypos - first->ypos;
        destroyCDKLabel(first);
        destroyCDKLabel(second);
    }

    auto selectionElems = getSelectionListElems();

    tourSelection = newCDKScroll(
            cdkScreen, CENTER, CENTER, RIGHT, height * 2, 55,
            "<C> Active tournaments\n   id |      name     | cur_users | max_users | key |",
            &selectionElems[0], selectionElems.size(), TRUE,
            A_REVERSE, TRUE, FALSE
            );


    bindCDKObject(vSCROLL, tourSelection, KEY_ENTER, activateScroll, &_vActiveTournaments);

    activateCDKScroll(tourSelection, nullptr);
}


char *convert(const std::string & s) {
    char *pc = new char[s.size()+1];
    std::strcpy(pc, s.c_str());
    return pc;
}

std::vector<char *> polytour::ui::MainMenuWindow::Impl::getSelectionListElems() {
    std::vector<char *> result;
    std::vector<std::string> preResult;

    auto tournamentAPI = _pCoordinator->getMainAPI().tournamentAPI();
    _vActiveTournaments = tournamentAPI->getTournaments(
            {.status_ = transport::Tournament::status_wait_for_participants()});
    for (const auto& tournament: _vActiveTournaments) {
        std::string valueStr = string_format("|%-15s|%-11d|%-11d|%-5d|",
                                             tournament.name.data(), tournament.cur_participants_num,
                                             tournament.max_participants_num, tournament.id);
        preResult.emplace_back(valueStr);
    }

    std::transform(preResult.begin(), preResult.end(), std::back_inserter(result), convert);
    return result;
}

void polytour::ui::MainMenuWindow::Impl::initTournamentInfo() {

}

static int activateScroll (EObjectType cdktype GCC_UNUSED, void *object GCC_UNUSED, void *clientData, chtype key) {
    auto activeTournaments = (std::vector<polytour::transport::Tournament>*)clientData;
    auto scroll = (CDKSCROLL*)object;
    auto curItemId = getCDKScrollCurrentItem(scroll);
    auto t = (*activeTournaments)[curItemId];
}

polytour::ui::MainMenuWindow::MainMenuWindow(const std::shared_ptr<ICoordinator>& coordinator):
_pImpl(std::make_unique<Impl>(coordinator)){
}

polytour::ui::MainMenuWindow::~MainMenuWindow() = default;
