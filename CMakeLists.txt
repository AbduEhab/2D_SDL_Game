cmake_minimum_required(VERSION 3.16)

project("SDL_GAME" VERSION 0.1.0)

add_subdirectory(src)

set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED on)

# include(CTest)
# enable_testing()

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

# target_precompile_headers(${PROJECT_NAME} )

target_compile_definitions(${PROJECT_NAME} PRIVATE
     $<$<CONFIG:Debug>:DEBUG_ONLY=1>
     $<$<CONFIG:RelWithDebInfo>:DEBUG_ONLY=1>
)

add_subdirectory(
     external/sdl
     external/sdl_mixer
)

add_subdirectory(
     external/sdl_image
     external/sdl_ttf
)

add_subdirectory(
     external/glm
)

target_include_directories(${PROJECT_NAME}
     PUBLIC external/sdl/include
     PUBLIC external/sdl_mixer/include
     PUBLIC external/sdl_image
     PUBLIC external/sdl_ttf
     PUBLIC external/glm/glm
)

target_link_directories(${PROJECT_NAME}
     PRIVATE external/sdl
     PRIVATE external/sdl_mixer
     PRIVATE external/sdl_image
     PRIVATE external/sdl_ttf
     PRIVATE external/glm/glm
)

target_link_libraries(${PROJECT_NAME} SDL2 SDL2_mixer SDL2_image SDL2_ttf glm lua)
