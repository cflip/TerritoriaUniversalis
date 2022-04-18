cmake_minimum_required(VERSION 3.5)
set(CMAKE_CXX_STANDARD 17)

project(TerritoriaUniversalis)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

find_package(SFML COMPONENTS system window graphics CONFIG REQUIRED)

set(SOURCES
	src/main.cpp
    src/Country.cpp
    src/Country.h
    src/Map.cpp
    src/Map.h
)

add_executable(TerritoriaUniversalis ${SOURCES})
target_link_libraries(TerritoriaUniversalis PRIVATE sfml-system sfml-graphics sfml-window)

# Copy resource files to build directory
add_custom_command(
        TARGET TerritoriaUniversalis POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/res $<TARGET_FILE_DIR:TerritoriaUniversalis>/res
        COMMENT "Copying resources" VERBATIM
)
