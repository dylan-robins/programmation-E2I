cmake_minimum_required(VERSION 3.1...3.21)

project(
  TP2
  VERSION 1.0
  LANGUAGES C)

add_library(processPool processPool.c processPool.h)

add_executable(mgrep mgrep.c)
add_executable(mgrepPool mgrepPool.c)
add_executable(test_exec test_exec.c)
add_executable(test_fork test_fork.c)

target_link_libraries(mgrepPool PRIVATE processPool)
