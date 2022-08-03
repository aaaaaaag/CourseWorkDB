//
// Created by denis on 03.08.2022.
//

#ifndef COURSEWORKDB_ITOURNAMENTFACADE_H
#define COURSEWORKDB_ITOURNAMENTFACADE_H

#include "Tournament.h"
#include <vector>

namespace polytour::bl {
    class ITournamentFacade {
    public:

        virtual ~ITournamentFacade() = default;

        virtual void create(const transport::Tournament& tournament) = 0;

        virtual void remove(const transport::Tournament& tournament) = 0;

        virtual std::vector<transport::Tournament> getTournaments(const transport::Tournament::search_t& search) = 0;
    };
}

#endif //COURSEWORKDB_ITOURNAMENTFACADE_H
