cmake_minimum_required(VERSION 3.12)
project(KeenclooEngine)

set(PROJECT_NAME 3d-game-engine)

add_subdirectory(EngineCore)
add_subdirectory(EngineEditor)

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT 3d-game-engine-editor)