cmake_minimum_required (VERSION 3.6)

project (BidDataSystem)

set(CMAKE_CXX_COMPILER "g++")

set (EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

aux_source_directory (src SRC_LIST)

include_directories (include)

add_executable (BigDataSystem ${SRC_LIST})