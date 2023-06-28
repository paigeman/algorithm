cmake_minimum_required(VERSION 3.25)
project(vjudge)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_STANDARD 11)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
add_executable(hdu-2639 dp/hdu-2639.c)
add_executable(uva-437 dp/uva-437.cpp)