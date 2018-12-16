cmake_minimum_required(VERSION 2.8)
project(lab_8_msg)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_STANDARD 14)

add_executable(cncr_rdr_0 concurrent_readers.cc)
add_executable(cncr_rdr_1 concurrent_readers.cc)
add_executable(cncr_rdr_2 concurrent_readers.cc)
