//
// Created by denis on 7/23/22.
//

#ifndef COURSEWORKDB_TOURNAMENTTRANSACTIONFACTORY_H
#define COURSEWORKDB_TOURNAMENTTRANSACTIONFACTORY_H

#include "ITournamentTransactionFactory.h"

namespace polytour::bl::transaction {
    class TournamentTransactionFactory: public ITournamentTransactionFactory {
    public:

        explicit TournamentTransactionFactory(transport::User curUser);

        void create(const transport::Tournament &tournament) override;

        void erase(const transport::Tournament &tournament) override;

        void join(const transport::Tournament &tournament) override;

        void leave(const transport::Tournament &tournament) override;

    private:

        transport::User _curUser;

    };
}


#endif //COURSEWORKDB_TOURNAMENTTRANSACTIONFACTORY_H
