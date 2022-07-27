//
// Created by denis on 19.07.2022.
//

#ifndef COURSEWORKDB_MATCHREPOSITORY_H
#define COURSEWORKDB_MATCHREPOSITORY_H

#include "Repository.h"

#include <utility>
#include "ORM/Match.h"

namespace polytour::db::repository {
    class MatchRepository: public Repository<Match> {
    public:

        explicit MatchRepository(std::shared_ptr<IConnection> conn):
                Repository<Match>(std::move(conn)) {}

    private:

    protected:
        utility::FieldSet toFieldSet(const Match &obj) override;

        utility::FieldSet toFieldSet(const Match::search_t &obj) override;

        Match fromFieldSet(const utility::FieldSet &field) override;

        Identity getIdentity() override;

    };
}

#endif //COURSEWORKDB_MATCHREPOSITORY_H
