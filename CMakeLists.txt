cmake_minimum_required(VERSION 3.6)
project(Project4)
find_package(GLUT REQUIRED)
include_directories(${GLUT_INCLUDE_DIRS})
link_directories(${GLUT_LIBRARY_DIRS})
add_definitions(${GLUT_DEFINITIONS})
if(NOT GLUT_FOUND)
    message(ERROR " GLUT not found!")
endif(NOT GLUT_FOUND)
#########################################################
# FIND OPENGL
#########################################################
find_package(OpenGL REQUIRED)
include_directories(${OpenGL_INCLUDE_DIRS})
link_directories(${OpenGL_LIBRARY_DIRS})
add_definitions(${OpenGL_DEFINITIONS})
if(NOT OPENGL_FOUND)
    message(ERROR " OPENGL not found!")
endif(NOT OPENGL_FOUND)
#########################################################
# Include Files
#########################################################
add_executable(Project4 src/glut.h main.cpp src/lighting.cpp src/lighting.h src/main.h src/geometry.h src/math.h)

########################################################
# Linking & stuff
#########################################################

# create the program "test"
target_link_libraries(Project4 ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} )
