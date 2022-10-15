cmake_minimum_required(VERSION 3.12)

set(CORE 3d-game-engine-core)

set(CORE_PUBLIC_INCLUDES
 include/Core/Application.hpp
 include/Core/Log.hpp
 include/Core/Event.hpp
)

set(CORE_PRIVATE_INCLUDES
 src/Core/Window.hpp
 src/Core/Rendering/OpenGL/ShaderProgram.hpp
 src/Core/Rendering/OpenGL/VertexBuffer.hpp
 src/Core/Rendering/OpenGL/VertexArray.hpp
)

set(CORE_PRIVATE_SOURCES
 src/Core/Application.cpp
 src/Core/Window.cpp
 src/Core/Rendering/OpenGL/ShaderProgram.cpp
 src/Core/Rendering/OpenGL/VertexBuffer.cpp
 src/Core/Rendering/OpenGL/VertexArray.cpp
)

set(CORE_ALL_SOURCES
	${CORE_PUBLIC_INCLUDES}
	${CORE_PRIVATE_INCLUDES}
	${CORE_PRIVATE_SOURCES}
)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES
	${CORE_ALL_SOURCES}
)

add_library(${CORE} STATIC 
	${CORE_ALL_SOURCES}
)

target_include_directories(${CORE} PUBLIC include)
target_include_directories(${CORE} PRIVATE src)
target_compile_features(${CORE} PUBLIC cxx_std_17)

add_subdirectory(../external/glfw ${CMAKE_CURRENT_BINARY_DIR}/glfw)
target_link_libraries(${CORE} PRIVATE glfw)

add_subdirectory(../external/spdlog ${CMAKE_CURRENT_BINARY_DIR}/spdlog)
target_link_libraries(${CORE} PRIVATE spdlog)

add_subdirectory(../external/glad ${CMAKE_CURRENT_BINARY_DIR}/glad)
target_link_libraries(${CORE} PRIVATE glad)


set(IMGUI_INCLUDES
 ../external/imgui/imgui.h
 ../external/imgui/backends/imgui_impl_glfw.h
 ../external/imgui/backends/imgui_impl_opengl3.h
)

set(IMGUI_SOURCES
 ../external/imgui/imgui.cpp
 ../external/imgui/backends/imgui_impl_glfw.cpp
 ../external/imgui/backends/imgui_impl_opengl3.cpp
 ../external/imgui/imgui_draw.cpp
 ../external/imgui/imgui_tables.cpp
 ../external/imgui/imgui_widgets.cpp
 ../external/imgui/imgui_demo.cpp
)

add_library(Imgui STATIC 
 ${IMGUI_INCLUDES}
 ${IMGUI_SOURCES}
)


target_include_directories(Imgui PUBLIC ../external)
target_include_directories(Imgui PUBLIC ../external/imgui)
target_link_libraries(Imgui PRIVATE glad glfw)

target_link_libraries(${CORE} PRIVATE Imgui)