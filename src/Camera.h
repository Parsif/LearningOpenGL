#pragma once

#include "global.h"

#include "glm/glm.hpp"

namespace opengl
{
	class Camera
	{
	private:
		glm::vec3 position_, front_, up_;
		glm::mat4 view_{};
		
	public:
		Camera(const glm::vec3& position, const glm::vec3& front, const glm::vec3& up);
		void move(Direction direction);
		void rotate(const glm::vec3 &target);
		[[nodiscard]] inline const auto& getViewMatrix() const { return view_; }
        [[nodiscard]] inline const auto& getGetPosition() const { return position_; }
    };
}

