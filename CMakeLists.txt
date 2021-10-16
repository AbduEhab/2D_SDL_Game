cmake_minimum_required(VERSION 3.16)

project("SDL_GAME")

add_subdirectory("src")

target_link_libraries(${PROJECT_NAME} SDL2 SDL2_image SDL2_mixer)

# set(CMAKE_INCLUDE_CURRENT_DIR ON)
