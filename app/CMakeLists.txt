
qt_add_resources(GestioTacheApp imageresources
    PREFIX "/dataFiles"
    FILES logo.png
)

add_executable(GestioTacheApp

    sourceFiles/main.cpp
    sourceFiles/appgestiotache.cpp
    headerFiles/appgestiotache.h
)

target_link_libraries(GestioTacheApp PRIVATE Qt6::Widgets)

set_target_properties(GestioTacheApp PROPERTIES
    WIN32_EXECUTABLE ON
    MACOSX_BUNDLE ON
)
