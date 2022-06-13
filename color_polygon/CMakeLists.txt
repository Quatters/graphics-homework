cmake_minimum_required(VERSION 3.10) # common to every CLion project
project(color_polygon) # project name

set(OpenGlLinkers -lglut -lGLU -lGL -lglfw) # setting all the Glut libraries as one variable.

add_executable(color_polygon main.cpp ) #common to all clion project

target_link_libraries(color_polygon ${OpenGlLinkers}) # linking opengl libraries to the project