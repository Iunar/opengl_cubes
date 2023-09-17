#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "shader.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <cglm/cglm.h>
#include "debug.h"

static void read_shader(const char* path, void* buffer, size_t size) {
    if(path == NULL) {
        ERROR_EXIT("read_shader received a null path...\n");
    }
    if(buffer == NULL) {
        ERROR_EXIT("read_shader received a null buffer...\n");
    }

    memset(buffer, 0, size);

    FILE* fp = fopen(path, "r");
    if(fp == NULL) {
        ERROR_EXIT("failed to openg %s...\n", path);
    }

    int bytes_read = fread(buffer, sizeof(char), size-1, fp);
    if(ferror(fp) != 0) {
        ERROR_EXIT("fread failed...\n");
    } else if(feof(fp) != 0) {
        printf("%s: end of file reached! :)\n", path);
    }
}

void create_program(const char* vertex_path, const char* fragment_path,
        GLuint* program) {

    if(vertex_path == NULL)
        ERROR_EXIT("create_program received a null vertex_path...\n");
    if(fragment_path == NULL)
        ERROR_EXIT("create_program recieved a null fragment_path...\n");
    if(program == NULL)
        ERROR_EXIT("create_program recieved a null program...\n");

    size_t buffer_size = 1024;
    char buffer[buffer_size];
    char* buf_p = buffer;
    memset(buffer, 0, buffer_size);

    read_shader(vertex_path, buffer, buffer_size-1);
    GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader, 1, (const GLchar * const *)&buf_p, NULL);
    glCompileShader(vertex_shader);
    check_handle_status(vertex_shader, GL_COMPILE_STATUS, false);

    read_shader(fragment_path, buffer, buffer_size-1);
    GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader, 1, (const GLchar * const *)&buf_p, NULL);
    glCompileShader(fragment_shader);
    check_handle_status(fragment_shader, GL_COMPILE_STATUS, false);

    *program = glCreateProgram();
    glAttachShader(*program, vertex_shader);
    glAttachShader(*program, fragment_shader);
    glLinkProgram(*program);

    check_handle_status(*program, GL_LINK_STATUS, true);

    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);
}

static void check_handle_status(GLuint handle, GLenum pname, bool is_program) {
    int success;
    GLsizei length;
    size_t log_size = 1024;
    GLchar error_log[log_size];

    if(!is_program) {
        glGetShaderiv(handle, pname, &success);
    } else {
        glGetProgramiv(handle, pname, &success);
    }

    if(!success) {
        if(!is_program)
            glGetShaderInfoLog(handle, log_size, &length, error_log);
        else
            glGetProgramInfoLog(handle, log_size, &length, error_log);

        fprintf(stderr, "%s\n", error_log);
        exit(-1);
    }
}

void uniform_float(const char* name, float data, GLuint program) {
    int loc = glGetUniformLocation(program, name);
    glUniform1f(loc, data);
}

void uniform_mat4(const char* name, mat4 data, GLuint program) {
    int loc = glGetUniformLocation(program, name);
    glUniformMatrix4fv(loc, 1, GL_FALSE, (const GLfloat*)data);
}

void uniform_vec3(const char* name, vec3 data, GLuint program) {
    int loc = glGetUniformLocation(program, name);
    glUniform3fv(loc, 1, data);
}
