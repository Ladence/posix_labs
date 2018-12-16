cmake_minimum_required(VERSION 3.9)
project(lab_9_shm)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_STANDARD 17)

add_executable(swaper swaper.cc)
add_executable(inc inc.cc)

add_executable(cncr_wrtr_0 concurrent_writers.cc)
add_executable(cncr_wrtr_1 concurrent_writers.cc)
add_executable(cncr_wrtr_2 concurrent_writers.cc)
