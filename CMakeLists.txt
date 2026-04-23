cmake_minimum_required(VERSION 3.20)
project(SpaceInvader)



set(CMAKE_CXX_STANDARD 17)

find_package(SFML 3.1 COMPONENTS Graphics REQUIRED)

add_executable(SpaceInvader
    main.cpp
    Animation.cpp
    Constants.cpp
    DrawText.cpp
    Enemy.cpp
    EnemyManager.cpp
    Player.cpp
    Ufo.cpp
        GameState.h
        Game.cpp
        Game.h
        MenuItem.cpp
        MenuItem.h
        Menu.cpp
        Menu.h
)

target_compile_definitions(SpaceInvader PRIVATE TRACY_ENABLE)

# Copia gli asset (PNG) nella cartella di build
file(COPY ${CMAKE_SOURCE_DIR}/assets DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

# Tracy
target_include_directories(SpaceInvader PRIVATE /usr/include/Tracy)
target_link_libraries(SpaceInvader PRIVATE
        SFML::Graphics
        TracyClient
)