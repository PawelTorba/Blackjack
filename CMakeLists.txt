cmake_minimum_required(VERSION 3.10)
project(BlackJackGUI LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SFML 3 REQUIRED COMPONENTS Graphics Window System)

add_executable(BlackJackGUI     
    main.cpp
    player.cpp
    dealer.cpp
    card.cpp
    deck.cpp
    game.cpp
)

target_link_libraries(BlackJackGUI
    PRIVATE
        SFML::Graphics
        SFML::Window
        SFML::System
)