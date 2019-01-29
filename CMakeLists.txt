cmake_minimum_required(VERSION 3.12)
set(CMAKE_CXX_STANDARD 14)

project(rtr-collection)

# Build GLFW
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
add_subdirectory(${PROJECT_SOURCE_DIR}/lib/glfw)

include_directories(${PROJECT_SOURCE_DIR}/src/common)
include_directories(${PROJECT_SOURCE_DIR}/includes)
include_directories(${PROJECT_SOURCE_DIR}/includes/glm)
include_directories(${PROJECT_SOURCE_DIR}/includes/stb)
include_directories(${PROJECT_SOURCE_DIR}/includes/LoadOBJ)

file(GLOB_RECURSE SRC ${PROJECT_SOURCE_DIR}/src/common/*.c* ${PROJECT_SOURCE_DIR}/src/common/*.h)
file(GLOB_RECURSE GLAD  ${PROJECT_SOURCE_DIR}/includes/glad/*.h* ${PROJECT_SOURCE_DIR}/includes/glad/*.c*)

add_executable(HelloTriangle ${SRC} ${PROJECT_SOURCE_DIR}/src/basic/01_HelloTriangle/helloTriangle.cpp ${GLAD})
target_link_libraries(HelloTriangle glfw) # Link glfw

add_executable(Cube ${SRC} ${PROJECT_SOURCE_DIR}/src/basic/02_Cube/cube.cpp ${GLAD})
target_link_libraries(Cube glfw) # Link glfw

add_executable(ScreenQuad ${SRC} ${PROJECT_SOURCE_DIR}/src/basic/03_ScreenQuad/screenQuad.cpp ${GLAD})
target_link_libraries(ScreenQuad glfw) # Link glfw


