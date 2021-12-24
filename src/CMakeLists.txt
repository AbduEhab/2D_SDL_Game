cmake_minimum_required (VERSION 3.8)

add_executable(${PROJECT_NAME}
    Main.cpp
    Game.cpp
    Entity.cpp
    EntityManager.cpp
    TextureManager.cpp
    AssetManager.cpp

)

set(CMAKE_INCLUDE_CURRENT_DIR ON)