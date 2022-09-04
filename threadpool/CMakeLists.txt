cmake_minimum_required(VERSION 3.20)

set(TARGET_NAME threadpool)

project(${TARGET_NAME})
  
set(SRCS pool.c pool.h debug.h debug.c condition.h condition.c)
 
add_library(${TARGET_NAME} SHARED ${SRCS})

target_include_directories(${TARGET_NAME} PUBLIC ./)

source_group(src FILES ${SRCS})

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
target_link_libraries(${TARGET_NAME} PUBLIC Threads::Threads)