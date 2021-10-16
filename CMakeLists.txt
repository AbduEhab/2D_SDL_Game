cmake_minimum_required(VERSION 3.16)

project("SDL_GAME")

add_subdirectory(src)

add_subdirectory(
    external/SDL
    external/SDL_ttf
    )

target_include_directories(${PROJECT_NAME}
    PUBLIC external/SDL/include
    PUBLIC external/SDL_ttf/include
)

target_link_directories(${PROJECT_NAME}
    PRIVATE external/SDL/src 
    PRIVATE external/SDL_ttf
)

target_link_libraries(${PROJECT_NAME} SDL2 SDL2_ttf)

set(CMAKE_INCLUDE_CURRENT_DIR ON)