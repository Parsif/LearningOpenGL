#include "Camera.h"

#include "glm/gtc/matrix_transform.hpp"


namespace opengl
{
	Camera::Camera(const glm::vec3& position, const glm::vec3& target_position, const glm::vec3& world_up) :
	        position_(position), target_position_(target_position), world_up_(world_up)
	{
		view_ = glm::lookAt(position_, target_position_, world_up_);
	}

    void Camera::move(Direction direction)
    {
        const float kCameraSpeed = 0.3f;
        switch (direction)
        {
            case Direction::up:
                position_ += target_position_ * kCameraSpeed;
                break;
            case Direction::down:
                position_ -= target_position_ * kCameraSpeed;
                break;
            case Direction::right:
                position_ += glm::normalize(glm::cross(target_position_, world_up_)) * kCameraSpeed;
                break;
            case Direction::left:
                position_ -= glm::normalize(glm::cross(target_position_, world_up_)) * kCameraSpeed;
                break;
        }
        view_ = glm::lookAt(position_, target_position_, world_up_);
    }

    void Camera::rotate(const glm::vec3 &target)
    {
        target_position_ = target;
        view_ = glm::lookAt(position_, target_position_, world_up_);
    }

}
