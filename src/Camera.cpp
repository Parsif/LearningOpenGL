#include "Camera.h"

#include <glm/gtc/matrix_transform.hpp>

namespace opengl
{
	Camera::Camera(const glm::vec3& position, const glm::vec3& front, const glm::vec3& up, const glm::mat4 &projection) :
            m_position(position), m_front(front), m_up(up), m_projection(projection)
	{
        m_view = glm::lookAt(m_position, m_position + m_front, m_up);
        m_view_projection = m_projection * m_view;
    }

    void Camera::translate(Direction direction)
    {
        const float kCameraSpeed = 0.15f;
        switch (direction)
        {
            case Direction::Up:
                m_position += m_front * kCameraSpeed;
                break;
            case Direction::Down:
                m_position -= m_front * kCameraSpeed;
                break;
            case Direction::Right:
                m_position += glm::normalize(glm::cross(m_front, m_up)) * kCameraSpeed;
                break;
            case Direction::Left:
                m_position -= glm::normalize(glm::cross(m_front, m_up)) * kCameraSpeed;
                break;
        }
        m_view = glm::lookAt(m_position, m_position + m_front, m_up);
        m_view_projection = m_projection * m_view;
    }

    void Camera::rotate(const glm::vec3 &target)
    {
        m_front = target;
        m_view = glm::lookAt(m_position, m_position + m_front, m_up);
        m_view_projection = m_projection * m_view;
    }

}
