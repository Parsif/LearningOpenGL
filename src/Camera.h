#pragma once

#include "glm/glm.hpp"

namespace opengl
{
	class Camera
	{
	private:
		glm::vec3 position_;
		glm::mat4 view_;
		
	public:
		Camera(const glm::vec3& position, const glm::vec3& target_position, const glm::vec3& up);
		[[nodiscard]] inline const auto& getViewMatrix() const { return view_; }
	};
}

