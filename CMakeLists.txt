cmake_minimum_required(VERSION 2.8)

project(libmla)

set(TARGET mla)

option(BUILD_TESTS "Build tests for libmla" OFF)

set(CMAKE_CXX_FLAGS "-std=c++0x -fPIC -O2 -funroll-loops -Wall")

set(VERSION_MAJOR 0)
set(VERSION_MINOR 1)

set(INSTALL_LIBRARY_DIR /usr/local/lib)
set(INSTALL_HEADER_DIR /usr/local/include/${TARGET})

set(HEADER_PATH ${CMAKE_CURRENT_SOURCE_DIR}/include/)
set(SOURCE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/src/)
set(TESTS_PATH ${CMAKE_CURRENT_SOURCE_DIR}/test/)

file(GLOB_RECURSE SOURCES ${SOURCE_PATH}/*)

include_directories(${HEADER_PATH})

#add_library(${TARGET} SHARED ${SOURCES})

#set_target_properties(${TARGET} PROPERTIES VERSION ${VERSION_MAJOR}.${VERSION_MINOR} SOVERSION ${VERSION_MAJOR})

if (BUILD_TESTS)
    set(TESTNAME runtest)
    add_executable(${TESTNAME}
        ${TESTS_PATH}/test.cpp
        ${TESTS_PATH}/DecisionTree_unittest.cpp)
    target_link_libraries(${TESTNAME} gtest.a -lpthread)
endif()

#install(TARGETS ${TARGET} LIBRARY DESTINATION ${INSTALL_LIBRARY_DIR} COMPONENT ${TARGET})
install(DIRECTORY ${HEADER_PATH} DESTINATION ${INSTALL_HEADER_DIR})
