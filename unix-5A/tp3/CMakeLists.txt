cmake_minimum_required(VERSION 3.1...3.21)

project(
  TP2
  VERSION 1.0
  LANGUAGES C)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -pedantic")

add_library(strUtils strUtils.c strUtils.h)

add_executable(test_pipe test_pipe.c)
add_executable(test_signal test_signal.c)

add_executable(test_signal_server test_signal_server.c)
add_executable(test_signal_client test_signal_client.c)

target_link_libraries(test_signal_client strUtils)

add_executable(time_providers time_providers.c)

add_executable(echo_dollar echo_dollar.c)
add_executable(test_stdin_override test_stdin_override.c)
add_executable(test_stdin_override_fifo test_stdin_override_fifo.c)
