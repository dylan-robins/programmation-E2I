cmake_minimum_required(VERSION 3.1...3.21)

project(
  TP4
  VERSION 1.0
  LANGUAGES C)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -pedantic -g")

add_executable(shmem_test shmem_test.c)
add_library(semaphores semaphores.c semaphores.h)
target_link_libraries(shmem_test semaphores)
