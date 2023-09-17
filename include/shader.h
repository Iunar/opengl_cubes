#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdbool.h>
#include <cglm/cglm.h>

void create_program(const char* vertex_path, const char* fragment_path,
        GLuint* program);
static void check_handle_status(GLuint handle, GLenum pname, bool is_program);
void uniform_float(const char* name, float data, GLuint program);
void uniform_mat4(const char* name, mat4 data, GLuint program);
void uniform_vec3(const char* name, vec3 data, GLuint program);

#endif // SHADER_H
