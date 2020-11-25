cmake_minimum_required(VERSION 3.0)
project(FlexC_src)

set(
    FILES
    interpreter.cpp
    lexical_analyzer.cpp
    parser.cpp
)

add_library(FlexC_src SHARED ${FILES})