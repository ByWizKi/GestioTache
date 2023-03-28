add_library(Tache STATIC
    tache.cpp
)
target_link_libraries(Tache PRIVATE Qt6::Core)
target_include_directories(Tache INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
