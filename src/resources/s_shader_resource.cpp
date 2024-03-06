#include "s_shader_resource.h"

Shader* SShaderResource::AddResource(const char* v_shader_file, const char* f_shader_file, const char* g_shader_file, std::string name) {
    res_[name] = LoadShaderFromFile(v_shader_file, f_shader_file, g_shader_file);
    return &res_[name];
}

Shader SShaderResource::GetResource(std::string name) {
    return res_[name];
}

void SShaderResource::DeleteResource(std::string res_name) {
    res_.erase(res_name);
    std::cout << "SUCCESS::" << res_name << "::was succesfullly deleted from shader resource!" << std::endl;
}

void SShaderResource::ClearAllResources() {
    for(const auto& itr : res_) {
        glDeleteProgram(itr.second.ID_);
    }
    std::cout << "SUCCESS::All shader resources were cleared!" << std::endl;
}

Shader SShaderResource::LoadShaderFromFile(const char *v_shader_source, const char *f_shader_source, const char *g_shader_source)
{
    // 1. retrieve the vertex/fragment source code from filePath
    std::string v_code;
    std::string f_code;
    std::string g_code;
    try
    {
        // open files
        std::ifstream vertexShaderFile(v_shader_source);
        std::ifstream fragmentShaderFile(f_shader_source);
        std::stringstream vShaderStream, fShaderStream;
        // read file's buffer contents into streams
        vShaderStream << vertexShaderFile.rdbuf();
        fShaderStream << fragmentShaderFile.rdbuf();
        // close file handlers
        vertexShaderFile.close();
        fragmentShaderFile.close();
        // convert stream into string
        v_code = vShaderStream.str();
        f_code = fShaderStream.str();
        // if geometry shader path is present, also load a geometry shader
        if (g_shader_source != nullptr)
        {
            std::ifstream geometryShaderFile(g_shader_source);
            std::stringstream gShaderStream;
            gShaderStream << geometryShaderFile.rdbuf();
            geometryShaderFile.close();
            g_code = gShaderStream.str();
        }
    }
    catch (std::exception e)
    {
        std::cout << "ERROR::SHADER: Failed to read shader files" << std::endl;
    }
    const char *v_shader = v_code.c_str();
    const char *f_shader = f_code.c_str();
    const char *g_shader = g_code.c_str();
    // 2. now create shader object from source code
    Shader shader;
    shader.Compile(v_shader, f_shader, g_shader_source != nullptr ? g_shader : nullptr);
    return shader;
}
