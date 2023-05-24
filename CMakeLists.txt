cmake_minimum_required(VERSION 3.8)
project(mig)

find_package(PostgreSQL REQUIRED)

set(LUAU_BUILD_CLI OFF CACHE INTERNAL "")
set(LUAU_BUILD_TESTS OFF CACHE INTERNAL "")
add_subdirectory(vendor/luau)

add_executable(mig
    src/block.cpp
    src/main.cpp
    src/postgresql.cpp
    src/script.cpp
    src/stringops.cpp
    src/world.cpp)
target_compile_features(mig PUBLIC cxx_std_17)
target_link_libraries(mig PostgreSQL::PostgreSQL Luau.Compiler Luau.VM)
