cmake_minimum_required(VERSION 3.16)

project("SDL_GAME")

add_subdirectory(src)



add_subdirectory(external/SDL)
add_subdirectory(external/SDL_ttf) 
add_subdirectory(external/glm)

SET(SDL2_ttf_DIR external/SDL_ttf)

find_package(SDL2_ttf CONFIG REQUIRED)

target_include_directories(${PROJECT_NAME}
    PUBLIC external/SDL/include
    PUBLIC external/SDL_ttf/include
)

target_link_directories(${PROJECT_NAME}
    PRIVATE external/SDL/src
    PRIVATE external/SDL_ttf
    PRIVATE ../external/glm
)

target_link_libraries(${PROJECT_NAME} SDL2 SDL2_ttf glm)

set(CMAKE_INCLUDE_CURRENT_DIR ON)