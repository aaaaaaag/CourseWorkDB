//
// Created by denis on 7/12/22.
//

#ifndef COURSEWORKDB_IIDENTIFIABLE_H
#define COURSEWORKDB_IIDENTIFIABLE_H

namespace polytour::db::repository {
    class IIdentifiable {
    public:
        virtual ~IIdentifiable() = default;

        virtual int getOID() = 0;
    };
}

#endif //COURSEWORKDB_IIDENTIFIABLE_H
