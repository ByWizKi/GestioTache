add_library(GestioTacheAppTexte SHARED
    sourceFiles/appgestiotachetexte.cpp
    headerFiles/appgestiotachetexte.h
)


target_link_libraries(GestioTacheAppTexte PRIVATE tache Qt6::Core)
target_include_directories(GestioTacheAppTexte INTERFACE ${CMAKE_INCLUDE_CURRENT_DIR})
