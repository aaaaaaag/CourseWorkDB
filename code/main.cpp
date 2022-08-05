#include "repositories/RepositoryFactory.h"
#include "repositories/roles/TournamentLeaderRole.h"

using namespace polytour::db;

int main() {
    repository::RepositoryFactory factory(std::make_shared<repository::roles::TournamentLeaderRole>());
    auto tournaments = factory.getTournamentRepository()->findObj({});
    int i = 0;
    return 0;
}
