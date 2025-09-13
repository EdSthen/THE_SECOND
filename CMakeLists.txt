cmake_minimum_required(VERSION 3.20)


project(MyProject LANGUAGES CXX)


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)


add_executable(my_app main.cpp)

target_sources(my_app PRIVATE main.cpp)
