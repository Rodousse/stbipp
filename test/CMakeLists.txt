
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG release-1.11.0
  GIT_SHALLOW ON
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_GetProperties(googletest)
if(NOT googletest_POPULATED)
  message(STATUS "Populating content of googletest")
  FetchContent_Populate(googletest)
  message(STATUS "    Sources in: ${googletest_SOURCE_DIR}")
  message(STATUS "    Binaries in: ${googletest_BINARY_DIR}")
endif()

add_subdirectory(${googletest_SOURCE_DIR} ${googletest_BINARY_DIR})

include(GoogleTest)
include(../cmake/TestUtils.cmake)

add_test(
  image_test
  SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/ImageTest.cpp
)

add_test(
  image_importer_test
  SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/ImageImporterTest.cpp
)

add_test(
  image_exporter_test
  SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/ImageExporterTest.cpp
)

add_test(
  color_test
  SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/ColorTest.cpp
)
