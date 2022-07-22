//
// Created by denis on 7/19/22.
//

#include "NotMandatoryField.h"
#include "gtest/gtest.h"

namespace polytour::db::tests::utility {

    TEST(NotMandatoryField, nullValue) {
        auto field = db::utility::NotMandatoryField<int>(std::nullopt);
        EXPECT_FALSE(field.hasValue());
        EXPECT_THROW(field.getValue(), std::logic_error);
        EXPECT_TRUE(field.isNull());
        EXPECT_NO_THROW(field.toNull());
    }

    TEST(NotMandatoryField, withValue) {
        auto field = db::utility::NotMandatoryField<int>(5);
        EXPECT_TRUE(field.hasValue());
        EXPECT_NO_THROW(field.getValue());
        EXPECT_FALSE(field.isNull());
        EXPECT_THROW(field.toNull(), std::logic_error);
    }
}