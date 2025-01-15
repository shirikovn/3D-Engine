cmake_minimum_required(VERSION 3.10)
project(3dEngine)

set(CMAKE_CXX_STANDARD 20)

find_package(SFML 3.0 COMPONENTS System Window Graphics Audio REQUIRED)
find_package(Eigen3 3.3 REQUIRED)

add_executable(3d_engine src/main.cpp)

target_link_libraries(3d_engine PRIVATE Eigen3::Eigen SFML::System SFML::Window SFML::Graphics SFML::Audio)