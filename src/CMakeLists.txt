cmake_minimum_required (VERSION 3.8)

add_executable(${PROJECT_NAME}
    Main.cc
    Game.cc
    Entity.cc
    EntityManager.cc
    TextureManager.cc
    AssetManager.cc

)

set(CMAKE_INCLUDE_CURRENT_DIR ON)