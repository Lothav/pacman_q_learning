cmake_minimum_required(VERSION 3.7.0 FATAL_ERROR)
project(Pacman_Q_Learning)

file(GLOB_RECURSE CORE_FILES src/main.cpp src/PacMaze/*)

add_executable(run ${CORE_FILES})