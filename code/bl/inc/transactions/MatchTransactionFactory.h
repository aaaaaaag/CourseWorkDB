//
// Created by denis on 04.08.2022.
//

#ifndef COURSEWORKDB_MATCHTRANSACTIONFACTORY_H
#define COURSEWORKDB_MATCHTRANSACTIONFACTORY_H

#include "IMatchTransactionFactory.h"
#include "repositories/roles/IRole.h"
#include <memory>

namespace polytour::bl::transaction {
    class MatchTransactionFactory: public IMatchTransactionFactory{
    public:

        MatchTransactionFactory(std::shared_ptr<db::repository::roles::IRole> role);

        void create(const transport::Match &match) override;

        void erase(const transport::Match &match) override;

        std::vector<transport::Match> getMatches(const transport::Match::search_t &search) override;

        void updateMatch(const transport::Match &curMatch, const transport::Match &newMatch) override;

    private:

        std::shared_ptr<db::repository::roles::IRole> _pRole;
        transport::User _curUser;

    };
}


#endif //COURSEWORKDB_MATCHTRANSACTIONFACTORY_H
