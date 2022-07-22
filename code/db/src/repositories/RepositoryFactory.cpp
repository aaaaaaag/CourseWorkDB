//
// Created by denis on 16.07.2022.
//

#include "repositories/RepositoryFactory.h"
#include "SqlConnection.h"
#include "PostgreSqlAdapter.h"
#include "utility/PostgreSqlCommandSource.h"

using namespace polytour::db::repository;

polytour::db::repository::RepositoryFactory::RepositoryFactory(const utility::FieldSet& connInfo):
_pConn(std::make_shared<SqlConnection>(
        std::make_shared<PostgreSqlAdapter>(connInfo),
        std::make_shared<utility::PostgreSqlCommandSource>())){
    _pUserRepo = std::make_unique<decltype(_pUserRepo)::element_type>(_pConn);
    _pTournamentRepo = std::make_unique<decltype(_pTournamentRepo)::element_type>(_pConn);
    _pMatchRepo = std::make_unique<decltype(_pMatchRepo)::element_type>(_pConn);
}

UserRepository* polytour::db::repository::RepositoryFactory::getUserRepository() {
    return _pUserRepo.get();
}

TournamentRepository* polytour::db::repository::RepositoryFactory::getTournamentRepository() {
    return _pTournamentRepo.get();
}

MatchRepository *RepositoryFactory::getMatchRepository() {
    return _pMatchRepo.get();
}

RepositoryFactory::~RepositoryFactory() {
    _pConn->commit();
}

