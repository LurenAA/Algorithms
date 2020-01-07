cmake_minimum_required(VERSION 3.0.0)
project(test2 VERSION 0.1.0)

include(CTest)
enable_testing()

SET(CMAKE_BUILD_TYPE "Debug")
SET(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g2 -ggdb")
add_executable(test2 chapter1/BinarySearch2.cpp)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
