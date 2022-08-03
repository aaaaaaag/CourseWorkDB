cmake_minimum_required(VERSION 3.21)
project(ui)

set(CMAKE_CXX_STANDARD 17)

add_library(${PROJECT_NAME}_lib STATIC
        ../transport/trash.cpp #TODO Remove this shit
        inc/IAuthorizationWindow.h
        inc/IWindowsFactory.h
        inc/IWindow.h)
target_include_directories(${PROJECT_NAME}_lib PUBLIC inc)

add_library(${PROJECT_NAME}_lib_cdk STATIC
        src/commonUser/CommonUserWindowsFactory.cpp
        inc/commonUser/CommonUserWindowsFactory.h
        src/AuthorizationWindow.cpp
        inc/AuthorizationWindow.h)
target_include_directories(${PROJECT_NAME}_lib_cdk PUBLIC inc)
target_link_libraries (${PROJECT_NAME}_lib_cdk cdk curses ${PROJECT_NAME}_lib)

add_executable(${PROJECT_NAME} src/main.cpp)

target_include_directories(${PROJECT_NAME} PUBLIC inc)
target_link_libraries(${PROJECT_NAME} ${PROJECT_NAME}_lib ${PROJECT_NAME}_lib_cdk)



