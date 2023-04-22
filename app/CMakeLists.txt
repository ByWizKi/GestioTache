cmake_minimum_required(VERSION 3.16)

project(GestioTacheApp VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTORCC ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core)

add_executable(GestioTacheApp
    sourceFiles/main.cpp
    sourceFiles/appgestiotache.cpp
    headerFiles/appgestiotache.h
)

qt_add_resources(GestioTacheApp "dataFiles"
    PREFIX "/"
    FILES dataFiles/imageFiles/logo.svg
        dataFiles/imageFiles/importantIcon.svg
        dataFiles/imageFiles/peuImportantIcon.svg
        dataFiles/imageFiles/urgentIcon.svg
        dataFiles/imageFiles/noneIcon.svg
        dataFiles/imageFiles/flecheDown.svg
        dataFiles/imageFiles/nextPreviousIcon.svg
        dataFiles/fontFiles/IBMPlexMono-Medium.ttf
        dataFiles/fontFiles/IBMPlexMono-Regular.ttf
        dataFiles/fontFiles/IBMPlexMono-SemiBold.ttf
        dataFiles/fontFiles/IBMPlexSans-Medium.ttf)

target_link_libraries(GestioTacheApp PRIVATE tache GestioTacheAppTexte Qt6::Widgets)

install(TARGETS GestioTacheApp DESTINATION ${CMAKE_SOURCE_DIR}/bin)


set_target_properties(GestioTacheApp PROPERTIES
    WIN32_EXECUTABLE ON
    MACOSX_BUNDLE ON)

if (WIN32)
    set(EXE_ICON "${CMAKE_SOURCE_DIR}/app/dataFiles/imageFiles/logo.svg")
    set_target_properties(GestioTacheApp PROPERTIES LINK_FLAGS "/ICON:\"${EXE_ICON}\"")
elseif (APPLE)
    set(EXE_ICON "${CMAKE_SOURCE_DIR}/app/dataFiles/imageFiles/logo.svg")
    set_target_properties(GestioTacheApp PROPERTIES MACOSX_BUNDLE_ICON_FILE "${EXE_ICON}")
endif (WIN32)