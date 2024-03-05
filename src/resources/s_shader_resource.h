#pragma once
#include "resource.h"
#include "shader.h"

class SShaderResource : public UResource<Shader> {
    public:
        Shader AddResource(const char* v_shader_file, const char* f_shader_file, const char* g_shader_file, std::string name) override;
        Shader GetResource(std::string name) override;
        void DeleteResource(std::string res_name) override;
        void ClearAllResources() override;
        Shader LoadShaderFromFile(const char *vShaderFile, const char *fShaderFile, const char *gShaderFile);
};