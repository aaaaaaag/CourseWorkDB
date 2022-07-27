cmake_minimum_required(VERSION 3.21)
project(db)

set(CMAKE_CXX_STANDARD 17)

add_library(${PROJECT_NAME} STATIC
        inc/public/IDatabaseAdapter.h
        inc/public/PostgreSqlAdapter.h
        src/PostgreSqlAdapter.cpp
        inc/public/IDatabaseExecResult.h
        inc/public/utility/FieldSet.h
        inc/private/pqxx/converters/ResultConverter.h
        inc/public/utility/ICommandSource.h
        src/utility/PostgreSqlCommandSource.cpp
        inc/public/utility/PostgreSqlCommandSource.h
        inc/public/repositories/Identity.h
        inc/public/utility/BaseDefines.h
        src/utility/TableAbstractValue.cpp
        inc/public/utility/TableAbstractValue.h
        inc/public/IConnection.h src/SqlConnection.cpp
        inc/public/SqlConnection.h
        inc/public/repositories/IRepository.h
        inc/public/repositories/IRepositoryInitializer.h
        inc/public/repositories/Repository.h
        inc/public/repositories/ORM/IIdentifiable.h
        inc/public/repositories/ORM/User.h
        src/repositories/UserRepository.cpp
        inc/public/repositories/UserRepository.h
        inc/public/repositories/ORM/Tournament.h
        inc/public/repositories/ORM/ISearchORM.h
        src/repositories/TournamentRepository.cpp
        inc/public/repositories/TournamentRepository.h
        inc/public/repositories/ORM/Match.h
        inc/public/utility/NotMandatoryField.h
        src/repositories/RepositoryFactory.cpp
        inc/public/repositories/RepositoryFactory.h
        inc/public/repositories/IRepositoryFactory.h src/repositories/MatchRepository.cpp inc/public/repositories/MatchRepository.h)

target_include_directories(${PROJECT_NAME} PUBLIC inc)
target_include_directories(${PROJECT_NAME} PUBLIC inc/public)


target_link_libraries(${PROJECT_NAME}  pqxx)

add_executable(${PROJECT_NAME}-tests
        tests/mocks/MockDatabaseAdapter.h
        tests/TestSqlConnection.cpp
        tests/mocks/MockDatabaseExecResult.h
        tests/mocks/MockCommandSource.h
        tests/TestPostgreSqlCommandSource.cpp
        tests/TestTableAbstractValue.cpp
        tests/NotMandatoryFieldTests.cpp
        tests/FieldSetTests.cpp)

target_link_libraries(${PROJECT_NAME}-tests ${PROJECT_NAME} gtest gmock gtest_main)

add_subdirectory(dependencies/libpqxx)
add_subdirectory(dependencies/googletest)

