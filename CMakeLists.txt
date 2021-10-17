cmake_minimum_required(VERSION 3.16)

project("SDL_GAME")

add_subdirectory(src)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED on)

# add_subdirectory(external/SDL)
# add_subdirectory(external/SDL_ttf) 
# add_subdirectory(external/glm)
# add_subdirectory(external/FreeType)

# SET(SDL2_ttf_DIR external/SDL_ttf)

# find_package(SDL2_ttf CONFIG REQUIRED)

# target_include_directories(${PROJECT_NAME}
#     PUBLIC external/SDL/include
#     PUBLIC external/SDL_ttf/include
# )

# target_link_directories(${PROJECT_NAME}
#     PRIVATE ${PROJECT_SOURCE_DIR}/external/SDL/src
#     PRIVATE ${PROJECT_SOURCE_DIR}/external/SDL_ttf
#     PRIVATE ${PROJECT_SOURCE_DIR}/external/glm
# )

find_package(glm REQUIRED)

target_link_libraries(${PROJECT_NAME} SDL2 SDL2_mixer SDL2_image SDL2_ttf glm lua)

# include_directories(${GLM_INCLUDE_DIRS})
# link_directories(${GLM_LIBRARY_DIRS})
# add_definitions(${GLM_DEFINITIONS})