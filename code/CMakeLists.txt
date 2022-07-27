cmake_minimum_required(VERSION 3.21)
project(CourseWorkDB)

set(CMAKE_CXX_STANDARD 17)

add_executable(${PROJECT_NAME} main.cpp)

add_subdirectory(db)

target_link_libraries(${PROJECT_NAME} db)
