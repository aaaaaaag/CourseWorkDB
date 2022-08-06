//
// Created by denis on 04.08.2022.
//

#ifndef COURSEWORKDB_MATCHFACADE_H
#define COURSEWORKDB_MATCHFACADE_H

#include "IMatchFacade.h"
#include <memory>
#include <transactions/IMatchTransactionFactory.h>

namespace polytour::bl::facade {
    class MatchFacade: public IMatchFacade{
    public:

        MatchFacade();

        void create(const transport::Match &match) override;

        void erase(const transport::Match &match) override;

        std::vector<transport::Match> getMatches(const transport::Match::search_t &search) override;


    private:

        std::unique_ptr<transaction::IMatchTransactionFactory> _pTransactionFactory;

    };
}


#endif //COURSEWORKDB_MATCHFACADE_H
