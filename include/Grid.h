#ifndef __GRID_H__
#define __GRID_H__

#include <vector>

#include <glad/glad.h>

#include "Camera.h"
#include "Shader.h"

class Grid {
  private:
    GLuint m_vao, m_vbo, m_ebo;
    std::vector<float> m_vertices{};
    std::vector<unsigned int> m_indices{};
    Shader m_shader;

  public:
    Grid() : m_shader{"shaders/grid.vert", "shaders/grid.frag"} { init(); }

    void render(const Camera& cam) {
        m_shader.use();
        m_shader.setMat4("view", cam.getViewMatrix());
        m_shader.setMat4("proj", cam.getPerspectiveProjection());

        glBindVertexArray(m_vao);
        glDrawElements(GL_TRIANGLES, m_indices.size(), GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
    }

  private:
    void init() {
        // here, the vertices creating the plane form a square, thus keeping the
        // fade out (relative to w) uniform to all directions, including diagonals
        m_vertices = std::vector<float>{
            0.0f,  0.0f, 0.0f,  1.0f,  // center with w = 1
            1.0f,  0.0f, 0.0f,  0.0f,  // infinitely distant +x (w = 0)
            1.0f,  0.0f, -1.0f, 0.0f,  //
            0.0f,  0.0f, -1.0f, 0.0f,  // infinitely distant -z
            -1.0f, 0.0f, -1.0f, 0.0f,  //
            -1.0f, 0.0f, 0.0f,  0.0f,  // infinitely distant -x
            -1.0f, 0.0f, 1.0f,  0.0f,  //
            0.0f,  0.0f, 1.0f,  0.0f,  // infinitely distant +z
            1.0f,  0.0f, 1.0f,  0.0f   //
        };

        m_indices = std::vector<unsigned int>{
            0, 1, 2,  // first quadrant
            0, 2, 3,  //
            0, 3, 4,  // second quadrant
            0, 4, 5,  //
            0, 5, 6,  // third
            0, 6, 7,  //
            0, 7, 8,  // fourth
            0, 8, 1,  //
        };

        glGenVertexArrays(1, &m_vao);
        glBindVertexArray(m_vao);

        glGenBuffers(1, &m_vbo);
        glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
        glBufferData(
            GL_ARRAY_BUFFER, sizeof(float) * m_vertices.size(), m_vertices.data(), GL_STATIC_DRAW
        );
        glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), nullptr);
        glEnableVertexAttribArray(0);

        glGenBuffers(1, &m_ebo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
        glBufferData(
            GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * m_indices.size(), m_indices.data(),
            GL_STATIC_DRAW
        );

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }
};

#endif
