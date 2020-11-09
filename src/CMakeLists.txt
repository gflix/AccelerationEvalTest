# list of source files which are compiled either for the release binary or for linking against the unittests
set(
    LIBRARY_SOURCE_FILES
    AccelerationEvaluation.c
)

# compile static library from the following source files
add_library(
    libacceleration-eval-test STATIC
    ${LIBRARY_SOURCE_FILES}
)

# add the root of this source tree to the include path
target_include_directories(
    libacceleration-eval-test
    PRIVATE ${CMAKE_SOURCE_DIR}/src ${CMAKE_BINARY_DIR}/src
)

# compile and link dependencies (both include paths and linker options are derived from this)
target_link_libraries(
    libacceleration-eval-test
    Threads::Threads
)

# build main executable
add_executable(
    acceleration-eval-test
    AccelerationEvalTest.c
)

# add the root of this source tree to the include path
target_include_directories(
    acceleration-eval-test
    PRIVATE ${CMAKE_SOURCE_DIR}/src ${CMAKE_BINARY_DIR}/src
)

# link binary against other libraries
target_link_libraries(
    acceleration-eval-test
    libacceleration-eval-test
)

install(
    TARGETS
    acceleration-eval-test
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

add_library(
    testable
    EXCLUDE_FROM_ALL
    STATIC
    ${LIBRARY_SOURCE_FILES}
)

target_include_directories(
    testable
    PRIVATE ${CMAKE_SOURCE_DIR}/src ${CMAKE_BINARY_DIR}/src
)

target_compile_options(
    testable
    PRIVATE
    -O2 -g -fprofile-arcs -ftest-coverage -coverage
)

target_link_libraries(
    testable
    Threads::Threads
)
