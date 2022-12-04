cmake_minimum_required(VERSION 3.23)
project(PairSimilarity C)

set(CMAKE_C_STANDARD 99)

add_executable(PairSimilarity src/main.c src/similarity.c src/similarity.h src/file.c src/file.h)
