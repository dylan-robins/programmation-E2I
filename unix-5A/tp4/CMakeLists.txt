cmake_minimum_required(VERSION 3.1...3.21)

project(
  TP4
  VERSION 1.0
  LANGUAGES C)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -pedantic")

add_library(semaphores semaphores.c semaphores.h)

add_executable(sem_test sem_test.c)
target_link_libraries(sem_test semaphores)

add_executable(ipc_parent_child ipc_parent_child.c)
target_link_libraries(ipc_parent_child semaphores)

add_executable(ipc_client ipc_client.c)
target_link_libraries(ipc_client semaphores)

add_executable(ipc_server ipc_server.c)
target_link_libraries(ipc_server semaphores)

add_executable(sem_process_pool_mgr sem_process_pool_mgr.c)
target_link_libraries(sem_process_pool_mgr semaphores)
