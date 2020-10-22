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

    void Camera::move(Direction direction)
    {
        const float kCameraSpeed = 0.3f;
        glm::vec3 pos;
        switch (direction)
        {
            case Direction::up:
                pos = front_ * kCameraSpeed;
                position_ += front_ * kCameraSpeed;
                break;
            case Direction::down:
                pos = front_ * kCameraSpeed;
                position_ -= front_ * kCameraSpeed;
                break;
            case Direction::right:
                pos = glm::normalize(glm::cross(front_, up_)) * kCameraSpeed;
                position_ += glm::normalize(glm::cross(front_, up_)) * kCameraSpeed;
                break;
            case Direction::left:
                pos = glm::normalize(glm::cross(front_, up_)) * kCameraSpeed;
                position_ -= glm::normalize(glm::cross(front_, up_)) * kCameraSpeed;
                break;
        }
        std::cout << "Translate: "<< pos.x  << " " << pos.y << " " << pos.z << '\n';

        std::cout << "Position: "<< position_.x  << " " << position_.y << " " << position_.z << '\n';
        view_ = glm::lookAt(position_, position_ + front_, up_);
    }

    void Camera::rotate(const glm::vec3 &target)
    {
        front_ = target;
        view_ = glm::lookAt(position_, position_ + front_, up_);
    }

}
