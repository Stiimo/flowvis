cmake_minimum_required(VERSION 3.16.0)
project(flowvis)
include(cmake/project_setup.cmake)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/static_lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/lib)
set(BUILD_SHARED_LIBS ON CACHE BOOL "Build shared libraries")

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt5 5.15 REQUIRED COMPONENTS Core Quick)

file(GLOB SOURCES src/*.cpp)
file(GLOB HEADERS src/*.h src/*.hpp)

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS} qml.qrc)

set_target_warnings(${PROJECT_NAME})

target_link_libraries(${PROJECT_NAME} PRIVATE
    Qt5::Core
    Qt5::Quick
)

target_compile_options(${PROJECT_NAME} PRIVATE "-Wno-useless-cast")
