#pragma once
#include "../utils/includes.h"
#include <fstream>
#include <sstream>

class Shader
{
public:
    unsigned int ID_;
    unsigned int type_;
    std::string name_;
    Shader(unsigned int type, std::string name) : type_(type), name_(name) {}
    Shader() {}
    ~Shader() {
        #ifdef SANDBOX_DEBUG 
            std::cout << "Shader is being destroyed!" << std::endl;
        #endif
    }
    Shader &Use();
    // No plans for using a geometry shader, so we'll set it to null by defualt
    void Compile(const char *vertex_source, const char *fragment_source, const char *geometry_source = nullptr);
    
    
    // uniform functions
    void setFloat(std::string name, float value, bool bUseShader = false);
    void setInteger(std::string name, int value, bool bUseShader = false);
    void setVector2f(std::string name, float x, float y, bool bUseShader = false);
    void setVector2f(std::string name, const glm::vec2 &value, bool bUseShader = false);
    void setVector3f(std::string name, float x, float y, float z, bool bUseShader = false);
    void setVector3f(std::string name, const glm::vec3 &value, bool bUseShader = false);
    void setVector4f(std::string name, float x, float y, float z, float w, bool bUseShader = false);
    void setVector4f(std::string name, const glm::vec4 &value, bool bUseShader = false);
    void setMat4(std::string name, const glm::mat4 &matrix, bool bUseShader = false);

private:
    void checkCompileErrors(unsigned int object, std::string type);
};
