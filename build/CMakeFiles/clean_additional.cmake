# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "app/CMakeFiles/GestioTacheApp_autogen.dir/AutogenUsed.txt"
  "app/CMakeFiles/GestioTacheApp_autogen.dir/ParseCache.txt"
  "app/GestioTacheApp_autogen"
  "appTexte/CMakeFiles/GestioTacheAppTexte_autogen.dir/AutogenUsed.txt"
  "appTexte/CMakeFiles/GestioTacheAppTexte_autogen.dir/ParseCache.txt"
  "appTexte/GestioTacheAppTexte_autogen"
  "tacheObjet/CMakeFiles/tache_autogen.dir/AutogenUsed.txt"
  "tacheObjet/CMakeFiles/tache_autogen.dir/ParseCache.txt"
  "tacheObjet/tache_autogen"
  "/home/enzoadmin/Desktop/GestioTache/doc/html"
  )
endif()
