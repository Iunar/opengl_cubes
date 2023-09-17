#include "texture.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "stb_image.h"
#include "debug.h"

texture_t create_texture(const char* path) {
    texture_t res;

    //---------> DEFAULTS FOR NOW <---------//
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);

    glTexParameteri(
            GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    //--------------------------------------//

    load_texture(path, &res);

    glGenTextures(1, &res.handle);
    glBindTexture(GL_TEXTURE_2D, res.handle);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, res.w, res.h, 0, GL_RGB,
            GL_UNSIGNED_BYTE, res.data);

    glGenerateMipmap(GL_TEXTURE_2D);

    return res;
}

static void load_texture(const char* path, texture_t* tex) {
    unsigned char *data = stbi_load(
            path, &tex->w, &tex->h, &tex->nrChannels, 0);
    tex->data = data;
    if(data == NULL) {
        ERROR_EXIT("failed to load image...\n");
    }
}

void bind_texture(texture_t texture) {
    glBindTexture(GL_TEXTURE_2D, texture.handle);
}

void destroy_texture_data(texture_t* tex) {
    stbi_image_free(tex->data);
}

/*
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);

glTexParameteri(
        GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

int width, height, nrChannels;
unsigned char *data = stbi_load(
        "gfx/container.jpg", &width, &height, &nrChannels, 0);

GLuint texture;
glGenTextures(1, &texture);

glBindTexture(GL_TEXTURE_2D, texture);
glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB,
        GL_UNSIGNED_BYTE, data);

glGenerateMipmap(GL_TEXTURE_2D);
stbi_image_free(data);
*/
