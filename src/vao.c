#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "vao.h"
#include "buffer.h"

VAO create_vao() {
    VAO vao;
    glGenVertexArrays(1, &vao.handle);
    return vao;
}

void set_vertex_attribute(size_t index, size_t element_count,
        GLenum data_type, GLboolean normalized, GLsizei stride, GLvoid* offset) {

    glVertexAttribPointer(index, element_count, data_type, normalized, stride, offset);
    glEnableVertexAttribArray(index);
}

void bind_vao(VAO vao) {
    glBindVertexArray(vao.handle);
}

void delete_vao(VAO vao) {
    glDeleteVertexArrays(1, &vao.handle);
}
