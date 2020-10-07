#include "Camera.h"

#include "glm/gtc/matrix_transform.hpp"

namespace opengl
{
	Camera::Camera(const glm::vec3& position, const glm::vec3& target_position, const glm::vec3& up) : position_(position)
	{
		view_ = glm::lookAt(position_, target_position, up);
	}

    void Camera::move(const float moveXAmount, const float moveYAmount)
    {

    }
}
