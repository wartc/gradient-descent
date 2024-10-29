cmake_minimum_required(VERSION 3.10)

project(gradient-descent VERSION 1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED true)

find_package(glfw3 3.3 REQUIRED)
find_package(glm CONFIG REQUIRED)

add_subdirectory(external/glad/)

add_executable(gradient-descent src/main.cpp)

target_link_libraries(gradient-descent glfw glm::glm glad)

target_include_directories(gradient-descent PUBLIC "${PROJECT_SOURCE_DIR}/include")
