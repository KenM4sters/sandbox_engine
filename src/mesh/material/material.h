#include "../../resources/shader.h"
#include "../../resources/s_shader_resource.h"
#include "../../utils/includes.h"

class Material {
    public:
        Material(SShaderResource* shader_resource, std::string name) : shader_resource_(shader_resource), name_(name) {
            if(!shader_resource_->res_.count(name))
                throw std::runtime_error("ERROR::Material name must be a valid shader resource key!");
            else
                material_ = shader_resource_->res_.find(name);
            
            material_->second.setVector3f("uColor", color_);
        }
        Shader* SetShaderMaterial(std::string shader_name); // takes in a name and searches the resource shader for that key
        Shader* GetShaderMaterial() { return &material_->second;}
    private:
        SShaderResource* shader_resource_;
        std::unordered_map<std::string, Shader>::iterator material_;
        std::string name_;

        glm::vec3 color_{0.3f, 0.8f, 0.8f};
};