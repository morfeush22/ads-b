cmake_minimum_required(VERSION 2.8 FATAL_ERROR)
project(ads-b)
include_directories(${PROJECT_SOURCE_DIR}/src)

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

add_executable(ads-b src/main.cpp)
add_dependencies(ads-b googletest)
