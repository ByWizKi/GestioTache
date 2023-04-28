cmake_minimum_required(VERSION 3.16)
project(GestioTache)

set(CMAKE_CONFIGURATION_TYPES "Release;RelWithDebInfo" CACHE STRING "" FORCE)

#================== INCLUSION DE QT =============#
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

#Définition de CMAKE_PREFIX_PATH
if(WIN32)
    set(CMAKE_PREFIX_PATH "ADD PATH" CACHE PATH "Qt path on Windows")
elseif(UNIX)
    set(CMAKE_PREFIX_PATH "/Applications/6.4.2/macos" CACHE PATH "Qt path on Linux")
endif()

find_package(Qt6Core REQUIRED)
find_package(Qt6Widgets REQUIRED)


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Doxygen REQUIRED)
set(DOXYGEN_GENERATE_HTML YES)
set(DOXYGEN_GENERATE_MAN NO)
set(DOXYGEN_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/doc")

doxygen_add_docs(
  doxygen
  ${CMAKE_SOURCE_DIR}/app/sourceFiles/appgestiotache.cpp
  ${CMAKE_SOURCE_DIR}/app/headerFiles/appgestiotache.h
  ${CMAKE_SOURCE_DIR}/appTexte/sourceFiles/appgestiotachetexte.cpp
  ${CMAKE_SOURCE_DIR}/appTexte/headerFiles/appgestiotachetexte.h
  ${CMAKE_SOURCE_DIR}/tacheObjet/sourceFiles/tache.cpp
  ${CMAKE_SOURCE_DIR}/tacheObjet/headerFiles/tache.h
)

qt_standard_project_setup()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")

add_subdirectory(app)
add_subdirectory(appTexte)
add_subdirectory(tacheObjet)
