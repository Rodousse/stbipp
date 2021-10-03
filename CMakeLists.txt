cmake_minimum_required(VERSION 3.12)

project(Stbipp
    VERSION 0.1.1
    LANGUAGES C CXX)


set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


option(BUILD_SHARED_LIBS "Build STBIPP as shared Library" ON)
option(STBIPP_BUILD_EXAMPLE "Build STBIPP examples" ON)

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
    src/stbipp/Color.inl
    src/stbipp/Image.hpp
    src/stbipp/ImageFormat.hpp
    src/stbipp/ImageExporter.hpp
    src/stbipp/ImageImporter.hpp)

set(INCLUDE_INSTALL_DIR ${CMAKE_INSTALL_PREFIX}/include)
set(STBIPP_INCLUDE_DIR ${CMAKE_INSTALL_PREFIX}/include/stbipp)

add_library(${PROJECT_NAME} ${STBIPP_SOURCES} ${STBIPP_HEADERS})


generate_export_header(${PROJECT_NAME}
  EXPORT_MACRO_NAME STBIPP_API
  EXPORT_FILE_NAME ${GENERATED_DIR}/stbipp/StbippSymbols.h
)

target_include_directories(${PROJECT_NAME} PRIVATE
    ${stb_content_SOURCE_DIR}
    PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
    $<BUILD_INTERFACE:${GENERATED_DIR}>
    $<INSTALL_INTERFACE:${INCLUDE_INSTALL_DIR}>
    )


if(NOT ${BUILD_SHARED_LIBS})
    target_compile_definitions(${PROJECT_NAME} PUBLIC STBIPP_STATIC_DEFINE)
endif()

if(${CMAKE_BUILD_TYPE} MATCHES Debug)
    set_target_properties(${PROJECT_NAME} PROPERTIES DEBUG_POSTFIX "d")
endif()

################################### Install/Packaging ##############################

set(CONFIG_INSTALL_DIR "${CMAKE_INSTALL_PREFIX}/lib/cmake/${PROJECT_NAME}")
set(TARGETS_EXPORT_NAME ${PROJECT_NAME}Target)

install(
    TARGETS
    ${PROJECT_NAME}
    EXPORT ${TARGETS_EXPORT_NAME}
    CONFIGURATIONS ${CMAKE_BUILD_TYPE}
    )
install(EXPORT ${PROJECT_NAME}Target NAMESPACE Stbipp:: DESTINATION ${CONFIG_INSTALL_DIR})


configure_package_config_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/cmake/StbippConfig.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/cmake/StbippConfig.cmake
    INSTALL_DESTINATION ${CONFIG_INSTALL_DIR}
    )

write_basic_package_version_file(
    ${CMAKE_CURRENT_BINARY_DIR}/cmake/StbippConfigVersion.cmake
    COMPATIBILITY SameMajorVersion
    )

install(
    DIRECTORY
    src/stbipp
    DESTINATION
    ${INCLUDE_INSTALL_DIR}
    FILES_MATCHING 
    PATTERN "*.hpp" 
    PATTERN "*.inl"
    )

install(
    FILES
    ${GENERATED_DIR}/stbipp/StbippSymbols.h
    DESTINATION
    ${STBIPP_INCLUDE_DIR}
    )
install(
    FILES
    ${CMAKE_CURRENT_BINARY_DIR}/cmake/StbippConfig.cmake
    ${CMAKE_CURRENT_BINARY_DIR}/cmake/StbippConfigVersion.cmake
    DESTINATION ${CONFIG_INSTALL_DIR}
    )


################################### Example ##############################

if(${STBIPP_BUILD_EXAMPLE})
    set(STBIPP_EX_SOURCES
        example/main.cpp)
    add_executable(stbipp_example ${STBIPP_EX_SOURCES})
    target_link_libraries(stbipp_example PRIVATE ${PROJECT_NAME})
    target_compile_definitions(stbipp_example PUBLIC -DRESOURCE_PATH="${CMAKE_CURRENT_SOURCE_DIR}/example")
endif()

