cmake_minimum_required(VERSION 3.16)

project("SDL_GAME")

add_subdirectory(src)

find_package(SDL_ttf CONFIG REQUIRED)

add_subdirectory(external/SDL2)
add_subdirectory(external/SDL2_ttf) 
add_subdirectory(external/glm)

target_include_directories(${PROJECT_NAME}
    PUBLIC external/SDL2/include
    PUBLIC external/SDL2_ttf/include
)

target_link_directories(${PROJECT_NAME}
    PRIVATE external/SDL2/src
    PRIVATE external/SDL2_ttf
    PRIVATE ../external/glm
)

target_link_libraries(${PROJECT_NAME} SDL2 SDL2_ttf glm)

set(CMAKE_INCLUDE_CURRENT_DIR ON)