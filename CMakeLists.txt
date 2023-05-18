cmake_minimum_required(VERSION 3.8)
project(mig)
add_executable(mig src/main.cpp)
target_compile_features(mig PUBLIC cxx_std_17)
