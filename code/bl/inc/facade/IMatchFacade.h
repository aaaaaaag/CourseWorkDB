//
// Created by denis on 03.08.2022.
//

#ifndef COURSEWORKDB_IMATCHFACADE_H
#define COURSEWORKDB_IMATCHFACADE_H

#include "Match.h"
#include <vector>

namespace polytour::bl::facade {
    class IMatchFacade {
    public:

        virtual ~IMatchFacade() = default;

        virtual void create(const transport::Match& match) = 0;

        virtual void erase(const transport::Match& match) = 0;

        virtual std::vector<transport::Match> getMatches(const transport::Match::search_t& search) = 0;
    };
}

#endif //COURSEWORKDB_IMATCHFACADE_H
