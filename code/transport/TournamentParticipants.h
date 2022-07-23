//
// Created by denis on 7/23/22.
//

#ifndef COURSEWORKDB_TOURNAMENTPARTICIPANTS_H
#define COURSEWORKDB_TOURNAMENTPARTICIPANTS_H

#include "IIdentifiable.h"
#include "NotMandatoryField.h"
#include <string>
#include <optional>

namespace polytour::transport {
    class TournamentParticipants: public IIdentifiable{
    public:
        int id;
        int tournament_id;
        int participant_id;
        int getOID() override {return id;}

        struct SearchTournamentParticipants{
            std::optional<decltype(id)> id_;
            std::optional<decltype(tournament_id)> tournament_id_;
            std::optional<decltype(participant_id)> participant_id_;
        };

        using search_t = SearchTournamentParticipants;
    };
}

#endif //COURSEWORKDB_TOURNAMENTPARTICIPANTS_H
