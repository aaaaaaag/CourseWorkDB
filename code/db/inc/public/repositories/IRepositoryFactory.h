//
// Created by denis on 16.07.2022.
//

#ifndef COURSEWORKDB_IREPOSITORYFACTORY_H
#define COURSEWORKDB_IREPOSITORYFACTORY_H

#include "UserRepository.h"
#include "TournamentRepository.h"
#include "MatchRepository.h"
#include "TournamentParticipantsRepository.h"

namespace polytour::db::repository {
    class IRepositoryFactory {
    public:

        virtual ~IRepositoryFactory() = default;

        virtual UserRepository* getUserRepository() = 0;

        virtual TournamentRepository* getTournamentRepository() = 0;

        virtual MatchRepository* getMatchRepository() = 0;

        virtual TournamentParticipantsRepository* getTournamentParticipantsRepository() = 0;

    };
}

#endif //COURSEWORKDB_IREPOSITORYFACTORY_H
