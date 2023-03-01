cmake_minimum_required(VERSION 3.8)

file(GLOB_RECURSE SRC_CXX_FILES CONFIGURE_DEPENDS *.cpp)
add_executable(${PROJECT_NAME}
    ${SRC_CXX_FILES}
)

# Copy Binary to DEV specified location
add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    $<TARGET_FILE_DIR:${PROJECT_NAME}>
    ${CMAKE_SOURCE_DIR}/bin/${CMAKE_GENERATOR_PLATFORM} # Change this to your Prefered location (I prefer ${CMAKE_SOURCE_DIR}/bin/$<CONFIG>/ or ${CMAKE_SOURCE_DIR}/bin/$<CMAKE_GENERATOR_PLATFORM>/)
)

add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/assets
    ${CMAKE_SOURCE_DIR}/bin/assets
)

add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/assets
    $<TARGET_FILE_DIR:${PROJECT_NAME}>/../assets
)

if(UNIX AND NOT APPLE)
    # Delete Cmake files
    add_custom_command(
        TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E remove_directory
        ${CMAKE_SOURCE_DIR}/bin/linux/CMakeFiles
    )

    add_custom_command(
        TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E remove
        ${CMAKE_SOURCE_DIR}/bin/linux/Makefile
    )

    add_custom_command(
        TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E remove
        ${CMAKE_SOURCE_DIR}/bin/linux/cmake_install.cmake
    )

else()

    add_custom_command(
        TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        ${CMAKE_BINARY_DIR}/external/SDL/$<CONFIG>/SDL2.dll
        ${CMAKE_SOURCE_DIR}/bin/${CMAKE_GENERATOR_PLATFORM}/SDL2.dll)

    add_custom_command(
        TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        ${CMAKE_BINARY_DIR}/external/SDL/$<CONFIG>/SDL2.dll
        $<TARGET_FILE_DIR:${PROJECT_NAME}>/SDL2.dll)

    add_custom_command(
        TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        ${CMAKE_BINARY_DIR}/external/sdl_image/$<CONFIG>/SDL2_image.dll
        ${CMAKE_SOURCE_DIR}/bin/${CMAKE_GENERATOR_PLATFORM}/SDL2_image.dll)

    add_custom_command(
        TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        ${CMAKE_BINARY_DIR}/external/sdl_image/$<CONFIG>/SDL2_image.dll
        $<TARGET_FILE_DIR:${PROJECT_NAME}>/SDL2_image.dll)
endif()

        
set(CMAKE_INCLUDE_CURRENT_DIR ON)