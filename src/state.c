#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "state.h"
#include <stdio.h>
#include <stdlib.h>

State state_new(int w, int h, const char* title, GLuint version_major,
        GLuint version_minor, GLenum profile,
    GLFWframebuffersizefun frame_buffer_callback,
    GLFWkeyfun key_callback) {

    return (State){
        .w = w, .h = h,
        .title = title,
        .version_major = version_major,
        .version_minor = version_minor,
        .profile = profile,
        .frame_buffer_callback = frame_buffer_callback,
        .key_callback = key_callback,
    };

}

void init_state(State* state) {

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, state->version_major);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, state->version_minor);
    glfwWindowHint(GLFW_OPENGL_PROFILE, state->profile);

    // fuck you tim cook
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    state->window = glfwCreateWindow(state->w, state->h, state->title, NULL, NULL);
    if(state->window == NULL) {
        fprintf(stderr, "failed to create window...\n");
        exit(-1);
    }

    glfwMakeContextCurrent(state->window);

    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        fprintf(stderr, "failed to init glad...\n");
        exit(-1);
    }

    glfwSetFramebufferSizeCallback(state->window, state->frame_buffer_callback);
    glfwSetKeyCallback(state->window, state->key_callback);

}
