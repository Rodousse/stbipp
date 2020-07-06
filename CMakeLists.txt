cmake_minimum_required(VERSION 3.12)

project(Stbipp
    VERSION 0.1.0
    LANGUAGES C CXX)


set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


option(STBIPP_SHARED "Build STBIPP as shared Library" ON)
option(STBIPP_BUILD_EXAMPLE "Build STBIPP examples" ON)
option(STBIPP_INSTALL "Enable if you wish to perform an install / Disable to use the lib as third party" OFF)

include(FetchContent)
include(CMakePackageConfigHelpers)
include(GenerateExportHeader)



# Path to use for cmake generated files
set(GENERATED_DIR "${CMAKE_CURRENT_BINARY_DIR}/generated")
message(STATUS "Generated files goes in : ${GENERATED_DIR}")
file(MAKE_DIRECTORY ${GENERATED_DIR})

################################### Retrieve STB ################################

FetchContent_Declare(
  stb_content
  GIT_REPOSITORY https://github.com/nothings/stb.git
)

FetchContent_GetProperties(stb_content)
if(NOT stb_content_POPULATED)
  FetchContent_Populate(stb_content)
endif()

message(STATUS ${stb_content_SOURCE_DIR})

################################### Implementation ##############################

set(STBIPP_SOURCES
    src/Image.cpp
    src/ImageExporter.cpp
    src/ImageFormat.cpp
    src/ImageImporter.cpp)

set(STBIPP_HEADERS
    src/stbipp/Color.hpp
    src/stbipp/Image.hpp
    src/stbipp/ImageFormat.hpp
    src/stbipp/ImageExporter.hpp
    src/stbipp/ImageImporter.hpp
    src/stbipp/TypeTraits.hpp)

set(INCLUDE_INSTALL_DIR ${CMAKE_INSTALL_PREFIX}/include)
set(STBIPP_INCLUDE_DIR ${CMAKE_INSTALL_PREFIX}/include/stbipp)

if(${STBIPP_SHARED})
    add_library(${PROJECT_NAME} SHARED ${STBIPP_SOURCES} ${STBIPP_HEADERS})
else()
    add_library(${PROJECT_NAME} STATIC ${STBIPP_SOURCES} ${STBIPP_HEADERS})
endif()


generate_export_header(${PROJECT_NAME}
  EXPORT_MACRO_NAME STBIPP_API
  EXPORT_FILE_NAME ${GENERATED_DIR}/StbippSymbols.h
)

target_include_directories(${PROJECT_NAME} PRIVATE
    ${stb_content_SOURCE_DIR}
    PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
    $<BUILD_INTERFACE:${GENERATED_DIR}>
    $<INSTALL_INTERFACE:${INCLUDE_INSTALL_DIR}>
    )


if(NOT ${STBIPP_SHARED})
    set_target_properties(${PROJECT_NAME} PROPERTIES COMPILE_FLAGS -DSTBIPP_STATIC_DEFINE)
endif()


################################### Install/Packaging ##############################

if(${STBIPP_INSTALL})

    set(CONFIG_INSTALL_DIR "${CMAKE_INSTALL_PREFIX}/lib/cmake/${PROJECT_NAME}")
    set(STBIPP_ROOT_DIR ${CMAKE_INSTALL_PREFIX})


    install(
        TARGETS
        ${PROJECT_NAME}
        EXPORT ${PROJECT_NAME}Target
        CONFIGURATIONS ${CMAKE_BUILD_TYPE}
        )
    install(EXPORT ${PROJECT_NAME}Target NAMESPACE Stbipp:: DESTINATION ${CONFIG_INSTALL_DIR})


    configure_package_config_file(
        ${CMAKE_CURRENT_SOURCE_DIR}/cmake/StbippConfig.cmake.in
        ${CMAKE_CURRENT_BINARY_DIR}/StbippConfig.cmake
        INSTALL_DESTINATION ${CONFIG_INSTALL_DIR}
        )

    write_basic_package_version_file(
        ${CMAKE_CURRENT_BINARY_DIR}/cmake/StbippConfigVersion.cmake
        COMPATIBILITY ExactVersion
        )

    install(
        DIRECTORY
        src/stbipp
        DESTINATION
        ${INCLUDE_INSTALL_DIR}
        FILES_MATCHING PATTERN "*.hpp"
        )

    install(
        FILES
        ${GENERATED_DIR}/StbippSymbols.h
        DESTINATION
        ${STBIPP_INCLUDE_DIR}
        )
    install(
        FILES
        ${CMAKE_CURRENT_BINARY_DIR}/StbippConfig.cmake
        ${CMAKE_CURRENT_BINARY_DIR}/cmake/StbippConfigVersion.cmake
        DESTINATION ${CONFIG_INSTALL_DIR}
        )
endif()


################################### Example ##############################

if(${STBIPP_BUILD_EXAMPLE})
    set(STBIPP_EX_SOURCES
        example/main.cpp)
    add_executable(stbipp_example ${STBIPP_EX_SOURCES})
    target_link_libraries(stbipp_example PRIVATE ${PROJECT_NAME})
    target_compile_definitions(stbipp_example PUBLIC -DRESOURCE_PATH="${CMAKE_CURRENT_SOURCE_DIR}/example")
endif()

