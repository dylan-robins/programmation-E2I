cmake_minimum_required(VERSION 3.1...3.21)

project(
  TP4
  VERSION 1.0
  LANGUAGES C)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -pthread -Wall -pedantic -g")

add_executable(tcat tcat.c)
add_executable(tmatrix tmatrix.c)
add_executable(philosophes philosophes.c)
                                     