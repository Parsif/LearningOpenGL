#ifndef LEARNINGOPENGL_SCENE_H
#define LEARNINGOPENGL_SCENE_H


#include <model/Model.h>

#include <vector>

namespace opengl
{
    class Scene
    {
    private:
        std::vector<Model> models_;
    public:
//        explicit Scene(std::initializer_list<T> list);
        void addModel(Model model);
        [[nodiscard]] inline auto&& getModels() const { return models_; };
    };
}



#endif //LEARNINGOPENGL_SCENE_H
