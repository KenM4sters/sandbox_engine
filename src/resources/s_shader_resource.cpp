#include "s_shader_resource.h"

Shader SShaderResource::AddResource(const char* v_shader_file, const char* f_shader_file, const char* g_shader_file, std::string name) {
    res_[name] = LoadShaderFromFile(v_shader_file, f_shader_file, g_shader_file);
    return res_[name];
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

Shader SShaderResource::LoadShaderFromFile(const char *vShaderFile, const char *fShaderFile, const char *gShaderFile)
{
    // 1. retrieve the vertex/fragment source code from filePath
    std::string vertexCode;
    std::string fragmentCode;
    std::string geometryCode;
    try
    {
        // open files
        std::ifstream vertexShaderFile(vShaderFile);
        std::ifstream fragmentShaderFile(fShaderFile);
        std::stringstream vShaderStream, fShaderStream;
        // read file's buffer contents into streams
        vShaderStream << vertexShaderFile.rdbuf();
        fShaderStream << fragmentShaderFile.rdbuf();
        // close file handlers
        vertexShaderFile.close();
        fragmentShaderFile.close();
        // convert stream into string
        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();
        // if geometry shader path is present, also load a geometry shader
        if (gShaderFile != nullptr)
        {
            std::ifstream geometryShaderFile(gShaderFile);
            std::stringstream gShaderStream;
            gShaderStream << geometryShaderFile.rdbuf();
            geometryShaderFile.close();
            geometryCode = gShaderStream.str();
        }
    }
    catch (std::exception e)
    {
        std::cout << "ERROR::SHADER: Failed to read shader files" << std::endl;
    }
    const char *vShaderCode = vertexCode.c_str();
    const char *fShaderCode = fragmentCode.c_str();
    const char *gShaderCode = geometryCode.c_str();
    // 2. now create shader object from source code
    Shader shader;
    shader.Compile(vShaderCode, fShaderCode, gShaderFile != nullptr ? gShaderCode : nullptr);
    return shader;
}
