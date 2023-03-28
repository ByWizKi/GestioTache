cmake_minimum_required(VERSION 3.5)

project(GestioTache VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

set(PROJECT_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/SourceFiles/main.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/SourceFiles/test.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/HeaderFiles/tache.h
    ${CMAKE_CURRENT_SOURCE_DIR}/SourceFiles/tache.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/SourceFiles/appgestiotachetexte.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/HeaderFiles/appgestiotachetexte.h
    ${CMAKE_CURRENT_SOURCE_DIR}/SourceFiles/appgestiotache.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/HeaderFiles/appgestiotache.h
    ${CMAKE_CURRENT_SOURCE_DIR}/SourceFiles/appgestiotache.ui
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(GestioTache
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET GestioTache APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(GestioTache SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(GestioTache
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(GestioTache PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

set_target_properties(GestioTache PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

install(TARGETS GestioTache
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(GestioTache)
endif()
