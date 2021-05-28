cmake_minimum_required(VERSION 3.1)

# Change the project name here
project(CPP-Chess)

## If you want to link SFML statically
# set(SFML_STATIC_LIBRARIES TRUE)

## In most cases better set in the CMake cache
set(SFML_DIR "C:\\SFML\\lib\\cmake\\SFML")

find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)
add_executable(CPP-Chess main.cpp)
target_link_libraries(CPP-Chess sfml-graphics sfml-audio)