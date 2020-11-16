#pragma once

#include "pch.h"
#include "ShaderProgram.h"

namespace opengl
{
    class Light
    {
    protected:
        glm::vec3 p_ambient, p_diffuse, p_specular;
        Light(const glm::vec3& ambient, const glm::vec3& diffuse, const glm::vec3& specular)
        : p_ambient(ambient), p_diffuse(diffuse), p_specular(specular)
        {
        }

    public:
        virtual void render(const ShaderProgram& shader_program) const
        {

        };
    };

    class DirectionLight : public Light
    {
    private:
        glm::vec3 direction;
    public:
        void render(const ShaderProgram& shader_program) const override
        {

        }
    };

    class PointLight : public Light
    {
    private:
        glm::vec3 m_position;
        float m_constant, m_linear, m_quadratic;

    public:
        PointLight(const glm::vec3& ambient, const glm::vec3& diffuse, const glm::vec3& specular, const glm::vec3& position,
                   float constant, float linear, float quadratic) : Light(ambient, diffuse, specular),
                   m_position(position), m_constant(constant), m_linear(linear), m_quadratic(quadratic)
        {
        }
        void render(const ShaderProgram &shader_program) const override
        {
            shader_program.useShaderProgram();
            shader_program.uniformVec3f("u_point_light.ambient", p_ambient);
            shader_program.uniformVec3f("u_point_light.diffuse", p_diffuse);
            shader_program.uniformVec3f("u_point_light.specular", p_specular);
            shader_program.uniformVec3f("u_point_light.position", m_position);
            shader_program.uniform1f("u_point_light.constant", m_constant);
            shader_program.uniform1f("u_point_light.linear", m_linear);
            shader_program.uniform1f("u_point_light.quadratic", m_quadratic);
        }
    };

    class SpotLight : public Light
    {
    public:
        glm::vec3 position, direction;
        float constant, linear, quadratic, cutoff;

    public:
        void render(const ShaderProgram &shader_program) const override
        {

        }
    };
}
