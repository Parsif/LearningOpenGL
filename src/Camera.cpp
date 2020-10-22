#include "Camera.h"

#include "glm/gtc/matrix_transform.hpp"

#include <iostream>

namespace opengl
{
	Camera::Camera(const glm::vec3& position, const glm::vec3& front, const glm::vec3& up) :
            position_(position), front_(front), up_(up)
	{
		view_ = glm::lookAt(position_, position_ + front_, up_);
	}

    void Camera::translate(Direction direction)
    {
        const float kCameraSpeed = 0.3f;
        switch (direction)
        {
            case Direction::up:
                position_ += front_ * kCameraSpeed;
                break;
            case Direction::down:
                position_ -= front_ * kCameraSpeed;
                break;
            case Direction::right:
                position_ += glm::normalize(glm::cross(front_, up_)) * kCameraSpeed;
                break;
            case Direction::left:
                position_ -= glm::normalize(glm::cross(front_, up_)) * kCameraSpeed;
                break;
        }
        view_ = glm::lookAt(position_, position_ + front_, up_);
    }

    void Camera::rotate(const glm::vec3 &target)
    {
        front_ = target;
        view_ = glm::lookAt(position_, position_ + front_, up_);
    }

}
