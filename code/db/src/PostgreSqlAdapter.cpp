//
// Created by denis on 10.06.2022.
//

#include "PostgreSqlAdapter.h"
#include "IDatabaseExecResult.h"
#include "private/pqxx/converters/ResultConverter.h"
#include "pqxx/pqxx"

class PostgreSqlExecResult: public polytour::db::IDatabaseExecResult {
public:

    explicit PostgreSqlExecResult(const pqxx::result& result):
            _fieldSet(polytour::db::priv::libpqxx::ResultConverter::toFieldSet(result))
            {};

    std::vector<polytour::db::utility::FieldSet> toFieldSetCollection() override {
        return _fieldSet;
    }

private:
    std::vector<polytour::db::utility::FieldSet> _fieldSet;
};

class polytour::db::PostgreSqlAdapter::PostgreSqlAdapterImpl {
public:

    explicit PostgreSqlAdapterImpl(const polytour::db::utility::FieldSet& connInfo):
        _conn(pqxx::connection(
                "user=" + connInfo["user"].toString() + " "
                "host=localhost "
                "password=" + connInfo["password"].toString() + " "
                "dbname=mydb"
        )),
        _transaction(_conn)
        {}

    std::shared_ptr<IDatabaseExecResult> executeSqlCommand(const std::string& command) {
        try {
            return std::make_shared<PostgreSqlExecResult>(_transaction.exec(command));
        }
        catch (std::exception& ex) {
            throw std::runtime_error("DB command execution error: " + std::string(ex.what()));
        }
    }

    void commit() {
        _transaction.commit();
    }

private:

    pqxx::connection _conn{};
    pqxx::work _transaction;

};

polytour::db::PostgreSqlAdapter::PostgreSqlAdapter(const polytour::db::utility::FieldSet& connInfo):
_pImpl(std::make_unique<PostgreSqlAdapterImpl>(connInfo))
{}

std::shared_ptr<polytour::db::IDatabaseExecResult>
polytour::db::PostgreSqlAdapter::executeSqlCommand(const std::string& command) {
    return _pImpl->executeSqlCommand(command);
}

void polytour::db::PostgreSqlAdapter::commit() {
    _pImpl->commit();
}

polytour::db::PostgreSqlAdapter::~PostgreSqlAdapter() = default;


