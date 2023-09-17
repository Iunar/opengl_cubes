#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cglm/cglm.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <stdint.h>

#include "globals.h"
#include "state.h"
#include "vao.h"
#include "buffer.h"
#include "shader.h"
#include "stb_image.h"
#include "texture.h"

#define EXIT(str) ({ \
        fprintf(stderr, str); \
        exit(-1); })

void frame_buffer_callback(GLFWwindow* window, int width, int height);
void key_callback(GLFWwindow* window, int key, int scancode,
        int action, int mods);

float player_cube[3] = {
    0.0f, 0.0f, 0.0f
};

struct entity {
    float* vertex_data;
    Buffer vbo;
};
typedef struct entity entity;

int main() {
    State state = state_new(1024, 768, "  ", 3, 3,
            GLFW_OPENGL_CORE_PROFILE, frame_buffer_callback, key_callback);

    init_state(&state);
    glEnable(GL_DEPTH_TEST);

    GLuint vertex_index = 0;
    GLuint texture_coord_index = 1;
    VAO vao = create_vao();
    bind_vao(vao);

    Buffer vbo = create_buffer(GL_ARRAY_BUFFER, false);
    bind_buffer(vbo);
    fill_buffer(vbo, 180*sizeof(float), textured_cube, GL_FLOAT);

    set_vertex_attribute(
        vertex_index, 3, GL_FLOAT, GL_FALSE, 5*sizeof(float), (void*)0);
    set_vertex_attribute(
        texture_coord_index,
        2, GL_FLOAT, GL_FALSE,
        5*sizeof(float), (void*)(3*sizeof(float))
    );

    GLuint shader_program;
    create_program(
            "shaders/vert.glsl", "shaders/default_f.glsl", &shader_program);

    vec3 iResolution = {(float)state.w, (float)state.h, 0.0f};
    uniform_vec3("iResolution", iResolution, shader_program);

    mat4 projection = GLM_MAT4_IDENTITY_INIT;
    float fov = 45.0f;
    glm_make_rad(&fov);
    glm_perspective(fov, 1024.0f / 768.0f, 0.1f, 100.0f, projection);
    int projection_loc = glGetUniformLocation(shader_program, "projection");

    mat4 view = GLM_MAT4_IDENTITY_INIT;
    glm_translate_z(view, -8.0f);
    int view_loc = glGetUniformLocation(shader_program, "view");

    texture_t container_tex = create_texture("gfx/container.jpg");
    destroy_texture_data(&container_tex);

    while(!glfwWindowShouldClose(state.window)) {

        glClearColor(0.0f, 0.25f, 0.25f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glUseProgram(shader_program);

        float u_time = (float)glfwGetTime();
        uniform_float("u_time", u_time, shader_program);

        // send projection & view uniforms
        uniform_mat4("view", view, shader_program);
        uniform_mat4("projection", projection, shader_program);

        float transforms[3][3] = {
            {2.0f, 3.0f, -8.0f},
            {player_cube[0], player_cube[1], 0.0f},
            {2.0f, -3.0f, -8.0f}
        };

        for(int i = 0; i < 3; ++i) {
            mat4 model = GLM_MAT4_IDENTITY_INIT;
            glm_translate_to(model, transforms[i], model);

            // rotate around origin
            if(i == 0) {
                float angle = 35.0f;
                glm_make_rad(&angle);
                glm_rotate_at(model, (vec3){-2.0f, -5.0f, 8.0f},
                        (float)glfwGetTime()* angle, (vec3){0.0f, 1.0f, 0.0f});
            } else if(i == 2) {
                float angle = 35.0f;
                glm_make_rad(&angle);
                glm_rotate_at(model, (vec3){-2.0f, 5.0f, 8.0f},
                        (float)glfwGetTime()* angle, (vec3){0.0f, 1.0f, 0.0f});
            }

            float rot_angle = -80.0f;
            glm_make_rad(&rot_angle);
            glm_rotate(model, (float)glfwGetTime() * rot_angle,
                    (vec3){0.5f, (i == 0 || i == 2) ? -1.0f : 0.25f, 0.0f});

            uniform_mat4("model", model, shader_program);

            bind_texture(container_tex);
            glBindVertexArray(vao.handle);
            glBindBuffer(GL_ARRAY_BUFFER, vbo.handle);
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }

        glfwSwapBuffers(state.window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

void frame_buffer_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void key_callback(GLFWwindow* window, int key, int scancode,
        int action, int mods) {
    if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }

    if(key == GLFW_KEY_UP && action == GLFW_REPEAT) {
        player_cube[0] += 0.25f;
    } else if (key == GLFW_KEY_DOWN && action == GLFW_REPEAT) {
        player_cube[0] -= 0.25f;
    }

    if(key == GLFW_KEY_F && action == GLFW_PRESS) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    } else if(key == GLFW_KEY_E && action == GLFW_PRESS) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
    } else if(action == GLFW_RELEASE) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }
}
