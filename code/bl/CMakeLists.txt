cmake_minimum_required(VERSION 3.21)
project(bl)

set(CMAKE_CXX_STANDARD 17)

add_library(${PROJECT_NAME} STATIC
        inc/IUserTransactionFactory.h
        inc/UserTransactionFactory.h
        src/UserTransactionFactory.cpp inc/ITournamentTransactionFactory.h src/TournamentTransactionFactory.cpp inc/TournamentTransactionFactory.h inc/IMatchTransactionFactory.h)

target_link_libraries(${PROJECT_NAME} transport db)
target_include_directories(${PROJECT_NAME} PUBLIC inc)