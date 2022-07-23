//
// Created by denis on 7/23/22.
//

#ifndef COURSEWORKDB_TOURNAMENTPARTICIPANTSREPOSITORY_H
#define COURSEWORKDB_TOURNAMENTPARTICIPANTSREPOSITORY_H

#include "Repository.h"
#include <utility>
#include "TournamentParticipants.h"

namespace polytour::db::repository {
    class TournamentParticipantsRepository: public Repository<transport::TournamentParticipants> {
    public:

        explicit TournamentParticipantsRepository(std::shared_ptr<IConnection> conn):
                Repository<transport::TournamentParticipants>(std::move(conn)) {}

    private:
    protected:
        utility::FieldSet toFieldSet(const transport::TournamentParticipants &obj) override;

        utility::FieldSet toFieldSet(const transport::TournamentParticipants::search_t &obj) override;

        transport::TournamentParticipants fromFieldSet(const utility::FieldSet &field) override;

        Identity getIdentity() override;
    };
}


#endif //COURSEWORKDB_TOURNAMENTPARTICIPANTSREPOSITORY_H
