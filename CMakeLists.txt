cmake_minimum_required(VERSION 3.10.2)

# set project name and version
file(STRINGS ".version" VERSION_FILE)
project(acceleration-eval-test VERSION ${VERSION_FILE} LANGUAGES C CXX)

# require compiler features
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED True)

# require external packages
find_package(Threads REQUIRED)

# import directory names used on GNU systems
include(GNUInstallDirs)

# import CMakeLists.txt from subdirectories
add_subdirectory(src)
add_subdirectory(unittest)

set(
    WITH_UNITTESTS FALSE CACHE
    BOOL "Add target gtest for compiling unittests, requires GTest sources in external/gtest"
)

if(WITH_UNITTESTS)
add_executable(
    gtest
    EXCLUDE_FROM_ALL
    ${LIBRARY_SOURCE_FILES}
    external/gtest/src/gtest-all.cc
)

target_include_directories(
    gtest
    PRIVATE ${CMAKE_SOURCE_DIR} ${CMAKE_SOURCE_DIR}/external/gtest ${CMAKE_SOURCE_DIR}/external/gtest/include
)

target_link_libraries(
    gtest
    -Wl,--whole-archive
    unittests
    testable
    -Wl,--no-whole-archive
    Threads::Threads
    -coverage
)

enable_testing()
add_test(gtest gtest)
endif(WITH_UNITTESTS)
