#pragma once

#include "pch.h"
#include "ShaderProgram.h"

namespace opengl
{
    class Light
    {
    protected:
        glm::vec3 p_ambient, p_diffuse, p_specular;
    };

    class DirectionLight : public Light
    {
    private:
        glm::vec3 m_direction;
    };

    class PointLight : public Light
    {
    private:
        glm::vec3 m_position;
        float m_constant, m_linear, m_quadratic;

    public:
        PointLight(const glm::vec3& ambient, const glm::vec3& diffuse, const glm::vec3& specular, const glm::vec3& position,
                   float constant, float linear, float quadratic)
        {

        }
        void render() const
        {

        }
    };

    class SpotLight : public Light
    {
    public:
        glm::vec3 position, direction;
        float constant, linear, quadratic, cutoff;

    public:
        void render(const ShaderProgram &shader_program) const
        {

        }
    };
}
