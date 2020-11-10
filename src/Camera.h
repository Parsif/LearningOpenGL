#pragma once

#include "global.h"
#include "pch.h"


namespace opengl
{
	class Camera
	{
	public:
		Camera(const glm::vec3& position, const glm::vec3& front, const glm::vec3& up, const glm::mat4 &projection);
		void translate(Direction direction);
		void rotate(const glm::vec3 &target);

		[[nodiscard]] inline const auto& getViewMatrix() const { return view_; }
        [[nodiscard]] inline const auto& getProjectionMatrix() const { return projection_; }
        [[nodiscard]] inline const auto& getGetPosition() const { return position_; }
        [[nodiscard]] inline const auto& getGetFront() const { return front_; }

    private:
        glm::vec3 position_, front_, up_;
        glm::mat4 view_, projection_;

    };
}

