cmake_minimum_required(VERSION 3.10) # common to every CLion project
project(concentric_rectangles) # project name

set(OpenGlLinkers -lglut -lGLU -lGL) # setting all the Glut libraries as one variable.

add_executable(concentric_rectangles main.cpp ) #common to all clion project

target_link_libraries(concentric_rectangles ${OpenGlLinkers}) # linking opengl libraries to the project