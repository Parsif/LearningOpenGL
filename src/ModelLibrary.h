#pragma once

#include "pch.h"

#include "model/Model.h"

namespace opengl
{
    class ModelLibrary
    {
    public:
        ModelLibrary() = default;
        ModelLibrary(const std::vector<std::string>& model_paths);
        [[nodiscard]] const Model& getModel(const std::string& model_path) const;
    private:
        std::unordered_map<std::string, Model> m_models;
    };
}





