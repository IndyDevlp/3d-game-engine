cmake_minimum_required(VERSION 3.12)

set(CORE 3d-game-engine-core)

set(CORE_PUBLIC_INCLUDES
 include/Core/Application.hpp
 include/Core/Log.hpp
 include/Core/Event.hpp
)

set(CORE_PRIVATE_INCLUDES
 src/Core/Window.hpp
)

set(CORE_PRIVATE_SOURCES
 src/Core/Application.cpp
 src/Core/Window.cpp
)

add_library(${CORE} STATIC 
	${CORE_PUBLIC_INCLUDES}
	
	${CORE_PRIVATE_INCLUDES}
	${CORE_PRIVATE_SOURCES}
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