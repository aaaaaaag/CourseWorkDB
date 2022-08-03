//
// Created by denis on 29.07.2022.
//

#ifndef COURSEWORKDB_IMATCHTRANSACTIONFACTORY_H
#define COURSEWORKDB_IMATCHTRANSACTIONFACTORY_H

#include "User.h"
#include "Match.h"
#include <vector>

namespace polytour::bl::transaction {
    class ITournamentTransactionFactory {
    public:

        virtual ~ITournamentTransactionFactory() = default;

        virtual void create(const transport::Tournament& tournament) = 0;

        virtual void erase(const transport::Tournament& tournament) = 0;

        virtual void join(const transport::Tournament& tournament) = 0;

        virtual void leave(const transport::Tournament& tournament) = 0;
    };
}

#endif //COURSEWORKDB_IMATCHTRANSACTIONFACTORY_H
