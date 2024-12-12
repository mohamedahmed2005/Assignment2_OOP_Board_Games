cmake_minimum_required(VERSION 3.26)
project(final_boaed_game_version)

set(CMAKE_CXX_STANDARD 17)

add_executable(final_boaed_game_version main.cpp
        BoardGame_Classes.h
        pyramid.h
        Word-Tic-tac-toe.h)
