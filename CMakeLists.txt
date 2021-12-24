cmake_minimum_required(VERSION 3.16)

project("SDL_GAME" VERSION 0.1.0)

add_subdirectory(src)

# Part till line 42 is taken from @lefticus

# Link this 'library' to use the standard warnings
add_library(project_warnings INTERFACE)

# Link this 'library' to set the c++ standard / compile-time options requested
add_library(project_options INTERFACE)

if(MSVC)
     target_compile_options(project_warnings INTERFACE /W4 /WX "/permissive-")
else()
     target_compile_features(project_options INTERFACE cxx_std_17)
     target_include_directories(project_options INTERFACE include external)

     target_compile_options(project_warnings
          INTERFACE -Wall
                    -Werror # treat all warnings as errors
                    -Wextra # reasonable and standard
                    -Wshadow # warn the user if a variable declaration shadows one from a parent context
                    -Wnon-virtual-dtor # warn the user if a class with virtual functions has a non-virtual destructor. This helps catch hard to track down memory errors
                    -Wold-style-cast # warn for c-style casts
                    -Wcast-align # warn for potential performance problem casts
                    -Wunused # warn on anything being unused
                    -Woverloaded-virtual # warn if you overload (not override) a virtual function
                    -Wpedantic # warn if non-standard C++ is used
                    -Wconversion # warn on type conversions that may lose data
                    -Wsign-conversion # warn on sign conversions
                    -Wnull-dereference # warn if a null dereference is detected
                    -Wdouble-promotion # warn if float is implicit promoted to double
                    -Wformat=2 # warn on security issues around functions that format output (ie printf)
                    
                    -Wattributes ## This part was not included by @lefticus
                    -Wreturn-local-addr
     )
endif()
#----------------------------------------------------------------------------------------------

# Part till line 62 is taken from @codetechandtutorials

#           DOWNLOAD ALL THE SUBMODULES
find_package(Git QUIET)
if(GIT_FOUND AND EXISTS "${PROJECT_SOURCE_DIR}/.git")
# Update submodules as needed
    option(GIT_SUBMODULE "Check submodules during build" ON)
    if(GIT_SUBMODULE)
        message(STATUS "Submodule update")
        execute_process(COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive
                        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                        RESULT_VARIABLE GIT_SUBMOD_RESULT)
        if(NOT GIT_SUBMOD_RESULT EQUAL "0")
            message(FATAL_ERROR "git submodule update --init failed with ${GIT_SUBMOD_RESULT}, please checkout submodules")
        endif()
    endif()
endif()

#----------------------------------------------------------------------------------------------

set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(TARGET ${PROJECT_NAME} CMAKE_CXX_STANDARD 17)
set(TARGET ${PROJECT_NAME} CMAKE_CXX_STANDARD_REQUIRED on)

# include(CTest)
# enable_testing()

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

target_compile_definitions(${PROJECT_NAME} PRIVATE
     $<$<CONFIG:Debug>:DEBUG=1>
     $<$<CONFIG:RelWithDebInfo>:DEBUG=1>
     $<$<CONFIG:Release>:NDEBUG=1>
)

add_subdirectory(
     external/sdl
)

add_subdirectory(
     external/sdl_mixer
)

add_subdirectory(
     external/sdl_image
)

add_subdirectory(
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
     PRIVATE build/external/external/sdl
     PRIVATE build/external/external/sdl_mixer
     PRIVATE build/external/external/sdl_image
     PRIVATE build/external/external/sdl_ttf
     PRIVATE build/external/external/glm
)

target_link_libraries(${PROJECT_NAME} SDL2 SDL2_mixer SDL2_image SDL2_ttf glm lua)
