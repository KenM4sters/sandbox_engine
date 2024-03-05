#pragma once

#include "../utils/includes.h"
#include <fstream>
#include <sstream>

class Shader
{
public:
    unsigned int ID;
    Shader() {}
    Shader &Use();
    // No plans for using a geometry shader, so we'll set it to null by defualt
    void Compile(const char *vertexSource, const char *fragmentSource, const char *geometrySource = nullptr);
    
    // uniform functions
    void setFloat(const char *name, float value, bool useShader = false);
    void setInteger(const char *name, int value, bool useShader = false);
    void setVector2f(const char *name, float x, float y, bool useShader = false);
    void setVector2f(const char *name, const glm::vec2 &value, bool useShader = false);
    void setVector3f(const char *name, float x, float y, float z, bool useShader = false);
    void setVector3f(const char *name, const glm::vec3 &value, bool useShader = false);
    void setVector4f(const char *name, float x, float y, float z, float w, bool useShader = false);
    void setVector4f(const char *name, const glm::vec4 &value, bool useShader = false);
    void setMat4(const char *name, const glm::mat4 &matrix, bool useShader = false);

private:
    void checkCompileErrors(unsigned int object, std::string type);
};
