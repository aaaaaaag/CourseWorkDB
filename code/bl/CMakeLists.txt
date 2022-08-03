cmake_minimum_required(VERSION 3.21)
project(bl)

set(CMAKE_CXX_STANDARD 17)

add_library(${PROJECT_NAME} STATIC
        inc/transactions/IUserTransactionFactory.h
        inc/transactions/UserTransactionFactory.h
        src/transactions/UserTransactionFactory.cpp inc/transactions/ITournamentTransactionFactory.h src/transactions/TournamentTransactionFactory.cpp inc/transactions/TournamentTransactionFactory.h inc/transactions/IMatchTransactionFactory.h src/AuthUserSingleton.cpp inc/AuthUserSingleton.h inc/facade/IMainFacade.h inc/facade/IUserFacade.h inc/facade/ITournamentFacade.h inc/facade/IMatchFacade.h)

target_link_libraries(${PROJECT_NAME} transport db)
target_include_directories(${PROJECT_NAME} PUBLIC inc)