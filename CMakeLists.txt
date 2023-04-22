cmake_minimum_required(VERSION 3.16)

project(GestioTache VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTORCC ON)


find_package(Qt6 REQUIRED COMPONENTS Widgets)
find_package(Doxygen REQUIRED)
set(DOXYGEN_GENERATE_HTML YES)
set(DOXYGEN_GENERATE_MAN NO)
set(DOXYGEN_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/doc")
set(DOXYGEN_EXAMPLE_PATH "${CMAKE_SOURCE_DIR}/example")
set(DOXYGEN_INPUT "${CMAKE_SOURCE_DIR}/src")

doxygen_add_docs(
  doxygen
  ${CMAKE_SOURCE_DIR}/doc
)
qt_standard_project_setup()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")

add_subdirectory(app)
add_subdirectory(appTexte)
add_subdirectory(tacheObjet)


