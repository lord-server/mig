cmake_minimum_required(VERSION 3.8)
project(mig)

find_package(PostgreSQL REQUIRED)

add_executable(mig
    src/main.cpp
    src/postgresql.cpp
    src/stringops.cpp
    src/world.cpp)
target_compile_features(mig PUBLIC cxx_std_17)
target_link_libraries(mig PostgreSQL::PostgreSQL)
