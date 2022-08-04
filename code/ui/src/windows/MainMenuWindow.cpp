//
// Created by denis on 04.08.2022.
//

#include "windows/MainMenuWindow.h"
#include <cdk/cdk.h>
#include <utility>
#include <vector>
#include <cstring>
#include <algorithm>

class polytour::ui::MainMenuWindow::Impl {
public:

    explicit Impl(std::shared_ptr<ICoordinator> coordinator):
    _pCoordinator(std::move(coordinator)){
        cdkScreen = initCDKScreen(nullptr);
        initCDKColor ();
    }

    ~Impl() {
        destroyCDKScreen (cdkScreen);
        endCDK ();
    }

private:

    void initTournamentList();
    std::vector<char*> getSelectionListElems();

    std::shared_ptr<ICoordinator> _pCoordinator;
    SScreen *cdkScreen;

};





void polytour::ui::MainMenuWindow::Impl::initTournamentList() {

    static const char *choices[] = {"   ","-->"};

    auto selectionElems = getSelectionListElems();

    auto selectionList = newCDKSelection(
            cdkScreen, CENTER, CENTER, RIGHT, 256, 256, "<C> Active tournaments ",
            &selectionElems[0], selectionElems.size(), (CDK_CSTRING2)choices, 2,
            A_REVERSE, TRUE, FALSE
            );



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
    auto activeTournaments = tournamentAPI->getTournaments(
            {.status_ = transport::Tournament::status_wait_for_participants()});
    for (const auto& tournament: activeTournaments) {
        preResult.emplace_back("name: " + tournament.name +
                               " participants: " + std::to_string(tournament.cur_participants_num) + "/" +
                               std::to_string(tournament.max_participants_num));
    }

    std::transform(preResult.begin(), preResult.end(), std::back_inserter(result), convert);
    return result;
}


polytour::ui::MainMenuWindow::MainMenuWindow(const std::shared_ptr<ICoordinator>& coordinator):
_pImpl(std::make_unique<Impl>(coordinator)){
}

polytour::ui::MainMenuWindow::~MainMenuWindow() = default;
