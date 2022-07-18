# add_test(NAME)
#
# Creates a test executable with the given name
# It can have the following arguments:
# Multiple value arguments
# - SOURCES: the sources needed to compile the test
# - LINK: list of linked libraries
# - HEADER_DIRS: list of header directories used for target_include_directories
# - DEFINITIONS: list of definitions to pass to the test
function(add_test NAME)
  set(options)
  set(oneValueArgs)
  set(multiValueArgs SOURCES LINK HEADER_DIRS DEFINITIONS)
  cmake_parse_arguments(TESTARGS "${options}" "${oneValueArgs}"
                        "${multiValueArgs}" ${ARGN} )
  message(STATUS "Creating test : ${NAME}")
  add_executable(${NAME} ${TESTARGS_SOURCES})
  target_link_libraries(${NAME} PRIVATE ${PROJECT_NAME} gtest_main ${TESTARGS_LINK})
  target_include_directories(${NAME} PRIVATE ${TESTARGS_HEADER_DIRS})
  target_compile_definitions(${NAME} PRIVATE ${TESTARGS_DEFINITIONS})
  gtest_discover_tests(${NAME})
endfunction()
