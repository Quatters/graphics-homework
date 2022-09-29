cmake_minimum_required(VERSION 3.10) # common to every CLion project
project(ray_tracing) # project name

set(OpenGlLinkers -lglut -lGLU -lGL) # setting all the Glut libraries as one variable.

add_executable(ray_tracing main.cpp ) #common to all clion project

target_link_libraries(ray_tracing ${OpenGlLinkers}) # linking opengl libraries to the project