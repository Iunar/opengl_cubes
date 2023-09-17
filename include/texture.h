#ifndef TEXTURE_H
#define TEXTURE_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

struct texture {
    GLuint handle;
    const char* path;
    int w;
    int h;
    int nrChannels;
    unsigned char *data;
};
typedef struct texture texture_t;

texture_t create_texture(const char* path);
static void load_texture(const char* path, texture_t* tex);
void destroy_texture_data(texture_t* tex);
void bind_texture(texture_t texture);

#endif // TEXTURE_H
