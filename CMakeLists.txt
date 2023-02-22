cmake_minimum_required(VERSION 3.13)

project(SDL_GAME VERSION 0.1.0 LANGUAGES CXX)
enable_language(CXX)

# ----------------------------------------------------------------------------------------------
# Part till line 71 is taken from @lefticus

# set a default CXX standard used by the external tools like clang-tidy, cppcheck, etc.
# You can later set fine-grained standards for each target using `target_compile_features`
set(CMAKE_CXX_STANDARD 20)

# ## Add project_options
# include(FetchContent)
# FetchContent_Declare(_project_options URL https://github.com/cpp-best-practices/project_options/archive/refs/heads/main.zip)
# FetchContent_MakeAvailable(_project_options)
# include(${_project_options_SOURCE_DIR}/Index.cmake)
include(CMakeSetupFiles/Index.cmake)

# run_vcpkg()

# Initialize project_options
# uncomment the options to enable them
if(MSVC)
    project_options(

        # ENABLE_CACHE
        # ENABLE_CONAN
        WARNINGS_AS_ERRORS
        # ENABLE_CPPCHECK
        # ENABLE_CLANG_TIDY
        # ENABLE_INCLUDE_WHAT_YOU_USE
        # ENABLE_COVERAGE
        # ENABLE_PCH
        # PCH_HEADERS <Eigen/Dense> <fmt/core.h> <vector> <utility> <string> <string_view>
        # ENABLE_DOXYGEN
        # ENABLE_IPO
        # ENABLE_USER_LINKER
        # ENABLE_BUILD_WITH_TIME_TRACE
        # ENABLE_UNITY
        # ENABLE_SANITIZER_ADDRESS
        # ENABLE_SANITIZER_LEAK
        # ENABLE_SANITIZER_UNDEFINED_BEHAVIOR
        # ENABLE_SANITIZER_THREAD
        # ENABLE_SANITIZER_MEMORY
        CLANG_WARNINGS "-Weverything"
    )
else()
    project_options(

        # ENABLE_CACHE
        # ENABLE_CONAN
        WARNINGS_AS_ERRORS
        # ENABLE_CPPCHECK
        # ENABLE_CLANG_TIDY
        # ENABLE_INCLUDE_WHAT_YOU_USE
        # ENABLE_COVERAGE
        # ENABLE_PCH
        # PCH_HEADERS <Eigen/Dense> <fmt/core.h> <vector> <utility> <string> <string_view>
        # ENABLE_DOXYGEN
        # ENABLE_IPO
        # ENABLE_USER_LINKER
        # ENABLE_BUILD_WITH_TIME_TRACE
        # ENABLE_UNITY
        # ENABLE_SANITIZER_ADDRESS
        # ENABLE_SANITIZER_LEAK
        # ENABLE_SANITIZER_UNDEFINED_BEHAVIOR
        # ENABLE_SANITIZER_THREAD
        # ENABLE_SANITIZER_MEMORY
    )
endif()

# ----------------------------------------------------------------------------------------------

# ----------------------------------------------------------------------------------------------
# Part till line 102 is very very similar to that of @codetechandtutorials

# DOWNLOAD ALL THE SUBMODULES
find_package(Git QUIET)

if(GIT_FOUND AND EXISTS "${PROJECT_SOURCE_DIR}/.git")
    # Update submodules as needed
    option(GIT_SUBMODULE "Check submodules during build" ON)

    if(NOT GIT_SUBMODULE) # Check submodules during build (SET TO 0 TO AVOID UPDATING)
        message(STATUS "Submodule update")

        if(1)
            execute_process(COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive
                WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                RESULT_VARIABLE GIT_SUBMOD_RESULT)
        else()
            execute_process(COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive --remote --merge
                WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                RESULT_VARIABLE GIT_SUBMOD_RESULT)
        endif()

        if(NOT GIT_SUBMOD_RESULT EQUAL "0")
            message(FATAL_ERROR "git submodule update --init --recursive failed with ${GIT_SUBMOD_RESULT}, please checkout submodules")
        endif()
    endif()
endif()

# ----------------------------------------------------------------------------------------------
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "RelWithDebInfo" CACHE STRING
        "Build not specified, defaulted to RelWithDebInfo" FORCE)
    message(STATUS "Build type not specified, defaulted to RelWithDebInfo")
endif(NOT CMAKE_BUILD_TYPE)

add_subdirectory(
    src
)

# Extra C++ specific option I need
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_20)

target_compile_definitions(${PROJECT_NAME} PRIVATE
     $<$<CONFIG:Debug>:DEBUG=1>
     $<$<CONFIG:RelWithDebInfo>:DEBUG=1>
     $<$<CONFIG:Release>:NDEBUG=1>
)

add_subdirectory(
     external/freetype
)

add_subdirectory(
     external/sdl
)

add_subdirectory(
     external/sdl_image
)

add_subdirectory(
     external/sdl_mixer
)

# add_subdirectory(
#      external/sdl_ttf
# )

add_subdirectory(
     external/glm
)

# file(GLOB_RECURSE SDL_INCLUDES CONFIGURE_DEPENDS /include/*.h)

# set CMAKE_PREFIX_PATH to the directory containing SDL2Config.cmake
set(SDL2_DIR external/sdl)

# find the SDL2 libraries
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)

# find_package(SDL2_mixer REQUIRED)


target_include_directories(${PROJECT_NAME}
     PUBLIC ${SDL2_INCLUDE_DIRS}
     PUBLIC external/sdl_mixer/include
     PUBLIC external/sdl_image
     PUBLIC external/sdl_ttf
     PUBLIC external/glm
     PUBLIC include/
)

target_link_directories(${PROJECT_NAME}
     PRIVATE external/sdl
     PRIVATE external/sdl_mixer
     PRIVATE external/sdl_image
     PRIVATE external/sdl_ttf
     PRIVATE external/glm
)

# find_file(SDL2_INCLUDE_DIR NAME SDL.h HINTS SDL2)
# find_library(SDL2_LIBRARY NAME SDL2)

target_link_libraries(${PROJECT_NAME}  ${SDL2_LIBRARIES} SDL2_image freetype SDL2_ttf glm )

