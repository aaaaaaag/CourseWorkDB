//
// Created by denis on 13.07.2022.
//

#ifndef COURSEWORKDB_TOURNAMENT_H
#define COURSEWORKDB_TOURNAMENT_H

#include "IIdentifiable.h"
#include "ISearchORM.h"
#include "utility/NotMandatoryField.h"
#include <string>
#include <optional>

namespace polytour::db::repository {
    class Tournament: public IIdentifiable{
    public:
        int id;
        std::string name;
        utility::NotMandatoryField<std::string> description;
        std::string status;
        int organizer_id;
        int max_participants_num;
        int cur_participants_num;

        int getOID() override {
            return id;
        }

        class SearchTournament: public ISearchORM{
        public:
            std::optional<decltype(id)> id_;
            std::optional<decltype(name)> name_;
            std::optional<decltype(description)> description_;
            std::optional<decltype(status)> status_;
            std::optional<decltype(organizer_id)> organizer_id_;
            std::optional<decltype(max_participants_num)> max_participants_num_;
            std::optional<decltype(cur_participants_num)> cur_participants_num_;
        };

        using search_t = SearchTournament;
    };
}

#endif //COURSEWORKDB_TOURNAMENT_H
