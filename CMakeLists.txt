cmake_minimum_required(VERSION 2.8.4)
project(cpp)

# CMake FindThreads is broken until 3.1
#find_package(Threads REQUIRED)
set(CMAKE_THREAD_LIBS_INIT pthread)

set(CMAKE_CXX_STANDARD 17)

set(EXT_PROJECTS_DIR ${PROJECT_SOURCE_DIR}/ext)
set(gtest_SOURCE_DIR ${EXT_PROJECTS_DIR}/googletest/googletest)


enable_testing()
include_directories(${gtest_SOURCE_DIR}/include)


set(GILDED_ROSE_SOURCE_FILES
        GildedRose.cc
        GildedRose.h
        )

set(GILDED_ROSE_UNIT_TESTS_SOURCE_FILES
        ${GILDED_ROSE_SOURCE_FILES}
        GildedRoseUnitTests.cc)

#set(SOURCE_FILES
#        ${GILDED_ROSE_SOURCE_FILES}
#        ${GILDED_ROSE_TEXT_TESTS_SOURCE_FILES})

add_subdirectory(${gtest_SOURCE_DIR} ${gtest_SOURCE_DIR}/bin EXCLUDE_FROM_ALL)
add_executable(GildedRose ${GILDED_ROSE_SOURCE_FILES} GildedRoseMain.cc)
#target_link_libraries(GildedRose gtest gtest_main ${CMAKE_THREAD_LIBS_INIT})
#target_link_libraries(GildedRose gtest gtest_main ${CMAKE_THREAD_LIBS_INIT})

add_executable(GildedRoseUnitTests ${GILDED_ROSE_UNIT_TESTS_SOURCE_FILES})
target_link_libraries(GildedRoseUnitTests gtest gtest_main ${CMAKE_THREAD_LIBS_INIT})
