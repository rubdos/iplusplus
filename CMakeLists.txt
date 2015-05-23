project(iplusplus)
cmake_minimum_required(VERSION 2.8)

find_package(Threads REQUIRED)

include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++14" COMPILER_SUPPORTS_CXX14)
CHECK_CXX_COMPILER_FLAG("-std=c++1y" COMPILER_SUPPORTS_CXX1Y)
if(COMPILER_SUPPORTS_CXX11)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
elseif(COMPILER_SUPPORTS_CXX1Y)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1y")
else()
    message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++14 support. Please use a different C++ compiler.")
endif()

add_subdirectory(mvcpp)

include_directories(${MVCPP_INCLUDE_DIRS})
include_directories(src)
message(STATUS "MVCPP include dirs: ${MVCPP_INCLUDE_DIRS}")

add_subdirectory(src)
file(COPY src/views DESTINATION ${CMAKE_BINARY_DIR}/src)
file(COPY src/static DESTINATION ${CMAKE_BINARY_DIR}/src)
