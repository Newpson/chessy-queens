add_subdirectory(context)
add_subdirectory(log)

add_executable(queens)
target_sources(queens
    PRIVATE main.c)
target_link_libraries(queens
    PUBLIC Queens Log)
