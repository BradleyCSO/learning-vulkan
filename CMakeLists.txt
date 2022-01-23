cmake_minimum_required(VERSION 3.16)
project(learning_vulkan)

set(CMAKE_CXX_STANDARD 17)
find_package(Vulkan REQUIRED)

add_subdirectory(glfw)
add_subdirectory(glm EXCLUDE_FROM_ALL)
SET(GLM_TEST_ENABLE OFF CACHE BOOL "GLM Build unit tests")

add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME} glfw ${GLFW_LIBRARIES} Vulkan::Vulkan)