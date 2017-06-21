cmake_minimum_required(VERSION 2.8 FATAL_ERROR)
project(ads-b)
include_directories(${PROJECT_SOURCE_DIR}/src)
include_directories(${PROJECT_SOURCE_DIR}/test)

if(CMAKE_CXX_COMPILER_ID MATCHES GNU)
    set(CMAKE_CXX_FLAGS "-Wall -Wno-unknown-pragmas -Wno-sign-compare -Woverloaded-virtual -Wwrite-strings -Wno-unused")
    set(CMAKE_CXX_FLAGS_DEBUG "-O0 -g3")
    set(CMAKE_CXX_FLAGS_RELEASE "-O3")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs -ftest-coverage")
endif()

set(GOOGLETEST_ROOT googletest/googletest)
include_directories(
    ${PROJECT_SOURCE_DIR}/${GOOGLETEST_ROOT}
    ${PROJECT_SOURCE_DIR}/${GOOGLETEST_ROOT}/include
)
set(GOOGLETEST_SOURCES
    ${PROJECT_SOURCE_DIR}/${GOOGLETEST_ROOT}/src/gtest-all.cc
    ${PROJECT_SOURCE_DIR}/${GOOGLETEST_ROOT}/src/gtest_main.cc
)
foreach(source ${GOOGLETEST_SOURCES})
    set_source_files_properties(${source} PROPERTIES GENERATED 1)
endforeach()
add_library(googletest ${GOOGLETEST_SOURCES})

add_executable(ads-b_ut test/main.cpp test/crc_calculator.cpp)
add_dependencies(ads-b_ut googletest)
target_link_libraries(ads-b_ut googletest pthread)
