#include "Camera.h"


namespace opengl
{
	Camera::Camera(const glm::vec3& position, const glm::vec3& front, const glm::vec3& up, const glm::mat4 &projection) :
            position_(position), front_(front), up_(up), projection_(projection)
	{
		view_ = glm::lookAt(position_, position_ + front_, up_);
    }

    void Camera::translate(Direction direction)
    {
        const float kCameraSpeed = 0.15f;
        switch (direction)
        {
            case Direction::Up:
                position_ += front_ * kCameraSpeed;
                break;
            case Direction::Down:
                position_ -= front_ * kCameraSpeed;
                break;
            case Direction::Right:
                position_ += glm::normalize(glm::cross(front_, up_)) * kCameraSpeed;
                break;
            case Direction::Left:
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
