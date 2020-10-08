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
        const glm::vec3 kFrontVec(0.0f, 0.0f, -1.0f);
        switch (direction)
        {
            case Direction::up:
                position_ += kFrontVec * kCameraSpeed;
                break;
            case Direction::down:
                position_ -= kFrontVec * kCameraSpeed;
                break;
            case Direction::right:
                position_ += glm::normalize(glm::cross(kFrontVec, world_up_)) * kCameraSpeed;
                break;
            case Direction::left:
                position_ -= glm::normalize(glm::cross(kFrontVec, world_up_)) * kCameraSpeed;
                break;
        }
        view_ = glm::lookAt(position_, target_position_, world_up_);
    }

}
