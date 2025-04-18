cmake_minimum_required(VERSION 3.10)
project(3dEngine)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_FLAGS_RELEASE "-O3")

include_directories(
    src/
)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.0
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)

include(FetchContent)
FetchContent_Declare(Eigen
    GIT_REPOSITORY https://gitlab.com/libeigen/eigen
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(Eigen)

set(SOURCES
    src/main.cpp
    src/stages/FragmentShaderStage/FragmentShaderStage.cpp
    src/stages/GeometryStage/GeometryStage.cpp
    src/stages/RasterizationStage/RasterizationStage.cpp
    src/stages/SceneLoaderStage/SceneLoader.cpp
    src/stages/WriteStage/WriteStage.cpp
    src/Renderer.cpp
    src/interaction/KeyBoardInteractor.cpp
    src/interaction/WindowManager.cpp
    src/parser/SimpleParser.cpp
)

add_executable(3d_engine ${SOURCES})

target_link_libraries(3d_engine PRIVATE Eigen3::Eigen SFML::System SFML::Window SFML::Graphics)
