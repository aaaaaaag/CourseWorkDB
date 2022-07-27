#include <iostream>
#include "public/PostgreSqlAdapter.h"
#include "utility/PostgreSqlCommandSource.h"

#include "repositories/UserRepository.h"
#include "SqlConnection.h"
#include "repositories/RepositoryFactory.h"
#include ""


using namespace polytour::db;

int main() {

    polytour::db::utility::FieldSet fieldSet;
    fieldSet.addPair("user", utility::FieldSet::value_t("myuser"));
    fieldSet.addPair("password", utility::FieldSet::value_t("mypass"));
    fieldSet.addPair("dbname", utility::FieldSet::value_t("mydb"));

    repository::RepositoryFactory factory(fieldSet);

    //repository::Transaction transaction(fieldSet);
    auto userRepo = factory.getUserRepository().lock();
    repository::User::search_t search;
    search.age_ = decltype(search.age_)::value_type{};
    auto res = userRepo->findObj(search);
    userRepo->addObj(res[0]);

    repository::RepositoryFactory factory2(fieldSet);
    auto userRepo1 = factory2.getUserRepository().lock();
    repository::User::search_t search1;
    search1.age_ = decltype(search1.age_)::value_type{};
    auto res1 = userRepo1->findObj(search1);
    userRepo1->addObj(res1[0]);
    return 0;
}
