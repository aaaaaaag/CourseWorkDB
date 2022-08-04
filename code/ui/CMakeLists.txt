cmake_minimum_required(VERSION 3.21)
project(ui)

set(CMAKE_CXX_STANDARD 17)

add_library(${PROJECT_NAME}_lib STATIC
        ../transport/trash.cpp #TODO Remove this shit
        inc/windows/IAuthorizationWindow.h
        inc/windows/IWindowsFactory.h
        inc/windows/IWindow.h inc/ICoordinator.h inc/windows/IMainMenuWindow.h)
target_include_directories(${PROJECT_NAME}_lib PUBLIC inc)

add_library(${PROJECT_NAME}_lib_cdk STATIC
        src/commonUser/CommonUserWindowsFactory.cpp
        inc/commonUser/CommonUserWindowsFactory.h
        src/windows/AuthorizationWindow.cpp
        inc/windows/AuthorizationWindow.h src/CdkCoordinator.cpp inc/CdkCoordinator.h src/windows/MainMenuWindow.cpp inc/windows/MainMenuWindow.h)
target_include_directories(${PROJECT_NAME}_lib_cdk PUBLIC inc)
target_link_libraries (${PROJECT_NAME}_lib_cdk cdk curses ${PROJECT_NAME}_lib transport bl)

add_executable(${PROJECT_NAME} src/main.cpp)

target_include_directories(${PROJECT_NAME} PUBLIC inc)
target_link_libraries(${PROJECT_NAME} ${PROJECT_NAME}_lib ${PROJECT_NAME}_lib_cdk)



