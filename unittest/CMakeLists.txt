# list of source files which are compiled for unit testing
set(
    UNITTEST_SOURCE_FILES
    AccelerationEvaluationTest.cpp

    gtest_main.cpp
)

# compile static library from the following source files
add_library(
    unittests
    EXCLUDE_FROM_ALL
    STATIC
    ${UNITTEST_SOURCE_FILES}
)

# add the root of this source tree to the include path
target_include_directories(
    unittests
    PRIVATE ${CMAKE_SOURCE_DIR}/src ${CMAKE_BINARY_DIR}/src ${CMAKE_SOURCE_DIR} ${CMAKE_SOURCE_DIR}/external/gtest/include
)

# compile and link dependencies (both include paths and linker options are derived from this)
target_link_libraries(
    unittests
    Threads::Threads
)
