cmake_minimum_required(VERSION 3.10) # common to every CLion project
project(param_curves) # project name

set(OpenGlLinkers -lglut -lGLU -lGL) # setting all the Glut libraries as one variable.

add_executable(param_curves main.cpp ) #common to all clion project

target_link_libraries(param_curves ${OpenGlLinkers}) # linking opengl libraries to the project