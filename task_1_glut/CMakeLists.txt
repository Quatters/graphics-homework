cmake_minimum_required(VERSION 3.10) # common to every CLion project
project(task_1_glut) # project name

set(OpenGlLinkers -lglut -lGLU -lGL) # setting all the Glut libraries as one variable.

add_executable(task_1_glut main.cpp ) #common to all clion project

target_link_libraries(task_1_glut ${OpenGlLinkers}) # linking opengl libraries to the project