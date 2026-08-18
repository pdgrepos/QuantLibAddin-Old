#include "py_enumregistry.hpp"

namespace ObjectHandler {

    // EnumTypeRegistry

    EnumTypeRegistry *EnumTypeRegistry::instance_;

    EnumTypeRegistry &EnumTypeRegistry::instance() {
        OH_REQUIRE(instance_, "Attempt to reference uninitialized EnumTypeRegistry object");
        return *instance_;
    }

    EnumTypeRegistry::AllTypeMap& EnumTypeRegistry::getAllTypesMap() const {
        static EnumTypeRegistry::AllTypeMap enumTypeMap_;
        return enumTypeMap_;
    }

    // EnumClassRegistry

    EnumClassRegistry *EnumClassRegistry::instance_;

    EnumClassRegistry &EnumClassRegistry::instance() {
        OH_REQUIRE(instance_, "Attempt to reference uninitialized EnumClassRegistry object");
        return *instance_;
    }

    EnumClassRegistry::AllTypeMap& EnumClassRegistry::getAllTypesMap() const {
        static EnumClassRegistry::AllTypeMap enumClassMap_;
        return enumClassMap_;
    }

    // EnumPairRegistry

    EnumPairRegistry *EnumPairRegistry::instance_;

    EnumPairRegistry &EnumPairRegistry::instance() {
        OH_REQUIRE(instance_, "Attempt to reference uninitialized EnumPairRegistry object");
        return *instance_;
    }

    EnumPairRegistry::AllTypeMap& EnumPairRegistry::getAllTypesMap() const {
        static EnumPairRegistry::AllTypeMap enumPairMap_;
        return enumPairMap_;
    }

}

