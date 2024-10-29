#ifndef __CAMERA_H__
#define __CAMERA_H__
#define GLM_ENABLE_EXPERIMENTAL

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/matrix.hpp>

class Camera {
  public:
    static constexpr glm::vec3 worldUp{0.0f, 1.0f, 0.0f};

  private:
    glm::vec3 m_pos{};
    glm::vec3 m_target{};
    glm::vec3 m_up{};
    float m_fov{45.0f};
    float m_aspectRatio{16.0f / 9.0f};
    float m_near{0.1f};
    float m_far{10.0f};

  public:
    Camera(
        const glm::vec3& position = glm::vec3(0.0f, 0.0f, 3.0f),
        const glm::vec3& target = glm::vec3(0.0f, 0.0f, 0.0f)
    ) {
        updateCameraOrientation(position, target);
    }

    glm::mat4 getViewMatrix() const { return glm::lookAt(m_pos, m_target, m_up); }

    glm::mat4 getPerspectiveProjection() const {
        return glm::perspective(m_fov, m_aspectRatio, m_near, m_far);
    }

    void setPosition(const glm::vec3& position) { updateCameraOrientation(position, m_target); }

    void look(const glm::vec3& target) { updateCameraOrientation(m_pos, target); }

  private:
    void updateCameraOrientation(const glm::vec3& pos, const glm::vec3& target) {
        m_pos = pos;
        m_target = target;

        glm::vec3 invDir = glm::normalize(m_pos - m_target);
        glm::vec3 right = glm::cross(worldUp, invDir);

        m_up = glm::cross(invDir, right);
    }
};

#endif
