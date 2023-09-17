#ifndef STATE_H
#define STATE_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

struct state {
    int w;
    int h;
    const char* title;
    GLenum version_major;
    GLenum version_minor;
    GLenum profile;
    GLFWframebuffersizefun frame_buffer_callback;
    GLFWkeyfun key_callback;
    GLFWwindow* window;
};
typedef struct state State;

State state_new(int w, int h, const char* title, GLuint version_major,
        GLuint version_minor, GLenum profile,
    GLFWframebuffersizefun frame_buffer_callback,
    GLFWkeyfun key_callback);

void init_state(State* state);


#endif // STATE_H
