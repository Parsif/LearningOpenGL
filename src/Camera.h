#pragma once

#include "global.h"

#include "glm/glm.hpp"

namespace opengl
{
	class Camera
	{
	private:
		glm::vec3 position_, target_position_, world_up_;
		glm::mat4 view_{};
		
	public:
		Camera(const glm::vec3& position, const glm::vec3& target_position, const glm::vec3& world_up);
		void move(Direction direction);
		[[nodiscard]] inline const auto& getViewMatrix() const { return view_; }
	};
}

