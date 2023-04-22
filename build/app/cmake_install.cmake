# Install script for directory: /Users/enzoadmin/Documents/CoursLyon/ConceptionApp/GestioTache/app

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

# Set default install directory permissions.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "/usr/bin/objdump")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/Users/enzoadmin/Documents/CoursLyon/ConceptionApp/GestioTache/bin/GestioTacheApp.app")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  file(INSTALL DESTINATION "/Users/enzoadmin/Documents/CoursLyon/ConceptionApp/GestioTache/bin" TYPE DIRECTORY FILES "/Users/enzoadmin/Documents/CoursLyon/ConceptionApp/GestioTache/bin/GestioTacheApp.app" USE_SOURCE_PERMISSIONS)
  if(EXISTS "$ENV{DESTDIR}/Users/enzoadmin/Documents/CoursLyon/ConceptionApp/GestioTache/bin/GestioTacheApp.app/Contents/MacOS/GestioTacheApp" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/Users/enzoadmin/Documents/CoursLyon/ConceptionApp/GestioTache/bin/GestioTacheApp.app/Contents/MacOS/GestioTacheApp")
    execute_process(COMMAND /usr/bin/install_name_tool
      -delete_rpath "/Users/enzoadmin/Documents/CoursLyon/ConceptionApp/GestioTache/build/appTexte"
      -delete_rpath "/Applications/6.4.2/macos/lib"
      -delete_rpath "/Users/enzoadmin/Documents/CoursLyon/ConceptionApp/GestioTache/build/tacheObjet"
      "$ENV{DESTDIR}/Users/enzoadmin/Documents/CoursLyon/ConceptionApp/GestioTache/bin/GestioTacheApp.app/Contents/MacOS/GestioTacheApp")
  endif()
endif()

