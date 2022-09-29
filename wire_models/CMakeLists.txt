cmake_minimum_required(VERSION 3.10) # common to every CLion project
project(wire_models) # project name

set(OpenGlLinkers -lglut -lGLU -lGL -lglfw) # setting all the Glut libraries as one variable.

add_executable(wire_models main.cpp ) #common to all clion project

target_link_libraries(wire_models ${OpenGlLinkers}) # linking opengl libraries to the project