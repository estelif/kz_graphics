#ifndef SHADERS_H
#define SHADERS_H
#include <GL/glew.h>

GLuint compileShader(const char* source, GLenum type);
GLuint createShaderProgram();

#endif
