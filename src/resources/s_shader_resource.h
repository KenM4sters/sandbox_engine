#pragma once
#include "resource.h"
#include "shader.h"

class SShaderResource : public UResource<Shader> {
    public:
        ~SShaderResource() {
            #ifdef SANDBOX_DEBUG 
                std::cout << "Shader Resource is being destroyed!" << std::endl;
            #endif
        }
        Shader* AddResource(const char* v_shader_file, const char* f_shader_file, const char* g_shader_file, std::string name, unsigned int type);
        void AddResource(std::string name, Shader* shader);
        Shader* GetResource(std::string name) override;
        void DeleteResource(std::string res_name) override;
        void ClearAllResources() override;
        Shader* LoadShaderFromFile(const char *vShaderFile, const char *fShaderFile, const char *gShaderFile);

};