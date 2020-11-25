#pragma once

#include "global.h"
#include "pch.h"

#include <glm/glm.hpp>

namespace opengl
{
	class Camera
	{
	public:
		Camera(const glm::vec3& position, const glm::vec3& front, const glm::vec3& up, const glm::mat4 &projection);
		void translate(Direction direction);
		void rotate(const glm::vec3 &target);

		[[nodiscard]] inline const auto& getViewMatrix() const { return m_view; }
        [[nodiscard]] inline const auto& getProjectionMatrix() const { return m_projection; }
        [[nodiscard]] inline const auto& getGetPosition() const { return m_position; }
        [[nodiscard]] inline const auto& getGetFront() const { return m_front; }
        [[nodiscard]] inline const auto& getViewProjection() const { return m_view_projection; }

    private:
        glm::vec3 m_position, m_front, m_up;
        glm::mat4 m_view, m_projection, m_view_projection;
    };
}

