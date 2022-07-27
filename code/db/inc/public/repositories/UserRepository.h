//
// Created by denis on 7/12/22.
//

#ifndef COURSEWORKDB_USERREPOSITORY_H
#define COURSEWORKDB_USERREPOSITORY_H

#include "Repository.h"

#include <utility>
#include "ORM/User.h"

namespace polytour::db::repository {
    class UserRepository: public Repository<User> {
    public:

        explicit UserRepository(std::shared_ptr<IConnection> conn):
                Repository<User>(std::move(conn)) {}

    private:

        utility::FieldSet toFieldSet(const User &obj) override;

        User fromFieldSet(const utility::FieldSet &field) override;

        utility::FieldSet toFieldSet(const User::search_t &obj) override;

        Identity getIdentity() override;
    };
}


#endif //COURSEWORKDB_USERREPOSITORY_H
