#include "ModelLibrary.h"

namespace opengl
{
    ModelLibrary::ModelLibrary(const std::vector<std::string>& model_paths)
    {
        for(auto& path : model_paths)
        {
            m_models.emplace(path, Model(path));
        }
    }

    // TODO: optimize
    const Model &ModelLibrary::getModel(const std::string& model_path) const
    {
        if(m_models.find(model_path) == m_models.end())
        {
            std::cerr << "Model " << model_path << " is not loaded\n";
        }
        return m_models.at(model_path);
    }
}