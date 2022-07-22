//
// Created by denis on 14.07.2022.
//

#ifndef COURSEWORKDB_NOTMANDATORYFIELD_H
#define COURSEWORKDB_NOTMANDATORYFIELD_H

#include <optional>
#include <stdexcept>

namespace polytour::db::utility {
    template <class T>
    class NotMandatoryField {
    public:
        using value_t = T;
        NotMandatoryField(): _value(std::nullopt){};
        explicit NotMandatoryField(const T& value): _value(value){};
        explicit NotMandatoryField(T&& value): _value(value){};
        explicit NotMandatoryField(std::nullopt_t null):_value(null){};

        [[nodiscard]] bool hasValue() const {return _value.has_value();}
        [[nodiscard]] bool isNull() const {return !_value.has_value();}
        [[nodiscard]] T getValue() const {
            if (!hasValue())
                throw std::logic_error("Attempt to get value from null");
            return _value.value();
        }
        [[nodiscard]] std::nullopt_t toNull() const {
            if (!isNull())
                throw std::logic_error("Attempt to get null from initialised field");
            return std::nullopt;
        }

    private:
        std::optional<T> _value;
    };
}

#endif //COURSEWORKDB_NOTMANDATORYFIELD_H
