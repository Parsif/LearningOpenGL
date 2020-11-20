#pragma once

#include "Components.h"

namespace opengl
{
    using EntityIdType = uint32_t;

    class EntityManager
    {
    private:
        ComponentMapType<TransformComponent> m_transform_components;
        ComponentMapType<PointLightComponent> m_point_light_components;

    private:
        template<class T>
        EntityIdType getNewId()
        {
            return 0;
        }

    public:
        void addPointLightComponent(EntityIdType entity_id)
        {
            if(m_point_light_components.find(entity_id) != m_point_light_components.end())
            {
                m_point_light_components[entity_id] = PointLightComponent();
            }
        }
        void addTransformComponent(EntityIdType entity_id)
        {
            if(m_point_light_components.find(entity_id) != m_point_light_components.end())
            {
                m_point_light_components[entity_id] = PointLightComponent();
            }
            else
            {
                std::cerr << "Entity already has this component\n";
            }
        }
    };
}




