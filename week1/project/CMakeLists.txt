cmake_minimum_required(VERSION 3.10)
project(TrigonometryLibrary)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

add_library(my_math STATIC
    src/ans_handler.cpp
    src/my_math.cpp
)

add_executable(main_app main.cpp)

target_link_libraries(main_app my_math)