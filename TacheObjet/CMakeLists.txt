add_library(tache SHARED

    sourceFiles/tache.cpp
    headerFiles/tache.h
)
target_link_libraries(tache PRIVATE Qt6::Core)
target_include_directories(tache PUBLIC ${CMAKE_INCLUDE_CURRENT_DIR})
