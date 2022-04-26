cmake_minimum_required(VERSION 3.10) # common to every CLion project
project(raster_algorithms) # project name

set(OpenGlLinkers -lglut -lGLU -lGL) # setting all the Glut libraries as one variable.

add_executable(raster_algorithms main.cpp ) #common to all clion project

target_link_libraries(raster_algorithms ${OpenGlLinkers}) # linking opengl libraries to the project