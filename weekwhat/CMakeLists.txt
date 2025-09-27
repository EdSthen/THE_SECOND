cmake_minimum_required(VERSION 3.10)
project(Blackjack)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCES
    src/main.cpp
    src/Card.cpp
    src/Deck.cpp
    src/Hand.cpp
    src/Player.cpp
    src/Dealer.cpp
    src/Game.cpp
)

set(HEADERS
    src/Card.h
    src/Deck.h
    src/Hand.h
    src/Player.h
    src/Dealer.h
    src/Game.h
)

add_executable(blackjack ${SOURCES} ${HEADERS})
