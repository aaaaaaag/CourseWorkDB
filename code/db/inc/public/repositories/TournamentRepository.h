//
// Created by denis on 14.07.2022.
//

#ifndef COURSEWORKDB_TOURNAMENTREPOSITORY_H
#define COURSEWORKDB_TOURNAMENTREPOSITORY_H

#include "Repository.h"

#include <utility>
#include "ORM/Tournament.h"

namespace polytour::db::repository {
    class TournamentRepository: public Repository<Tournament> {
    public:

        explicit TournamentRepository(std::shared_ptr<IConnection> conn):
                Repository<Tournament>(std::move(conn)) {}

    private:

        utility::FieldSet toFieldSet(const Tournament &obj) override;

        Tournament fromFieldSet(const utility::FieldSet &field) override;

        utility::FieldSet toFieldSet(const Tournament::search_t &obj) override;

        Identity getIdentity() override;
    };
}



#endif //COURSEWORKDB_TOURNAMENTREPOSITORY_H
