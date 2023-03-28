add_library(GestioTacheAppTexte STATIC
    appgestiotachetexte.cpp
)

target_link_libraries(GestioTacheAppTexte PRIVATE Qt6::Core)
target_include_directories(GestioTacheAppTexte INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
