cmake_minimum_required(VERSION 3.12)

set(EDITOR 3d-game-engine-editor)

add_executable(${EDITOR} src/main.cpp)

target_link_libraries(${EDITOR} 3d-game-engine-core Imgui glm)

target_compile_features(${EDITOR} PUBLIC cxx_std_17)

set_target_properties(${EDITOR} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/)