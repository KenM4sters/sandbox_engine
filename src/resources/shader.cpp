#include "shader.h"

Shader& Shader::Use()
{
    std::cout << this->ID_ << std::endl;
    glUseProgram(this->ID_);
    return *this;
}

void Shader::Compile(const char* vertex_source, const char* fragment_source, const char* geometry_source)
{
    unsigned int s_vertex, s_fragment, g_shader;

    // vertex Shader
    s_vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(s_vertex, 1, &vertex_source, NULL);
    glCompileShader(s_vertex);
    checkCompileErrors(s_vertex, "VERTEX");

    // fragment Shader
    s_fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(s_fragment, 1, &fragment_source, NULL);
    glCompileShader(s_fragment);
    checkCompileErrors(s_fragment, "FRAGMENT");

    // if geometry shader source code is given, also compile geometry shader
    if (geometry_source != nullptr)
    {
        g_shader = glCreateShader(GL_GEOMETRY_SHADER);
        glShaderSource(g_shader, 1, &geometry_source, NULL);
        glCompileShader(g_shader);
        checkCompileErrors(g_shader, "GEOMETRY");
    }
    // shader program
    this->ID_ = glCreateProgram();
    glAttachShader(this->ID_, s_vertex);
    glAttachShader(this->ID_, s_fragment);
    if (geometry_source != nullptr)
        glAttachShader(this->ID_, g_shader);
    glLinkProgram(this->ID_);
    checkCompileErrors(this->ID_, "PROGRAM");
    // shaders can be deleted now, since we've already linked them to our shaderProgram
    glDeleteShader(s_vertex);
    glDeleteShader(s_fragment);
    if (geometry_source != nullptr)
        glDeleteShader(g_shader);
}

void Shader::setFloat(const char *name, float value, bool bUseShader)
{
    if (bUseShader)
        this->Use();
    glUniform1f(glGetUniformLocation(this->ID_, name), value);
}
void Shader::setInteger(const char *name, int value, bool bUseShader)
{
    if (bUseShader)
        this->Use();
    glUniform1i(glGetUniformLocation(this->ID_, name), value);
}
void Shader::setVector2f(const char *name, float x, float y, bool bUseShader)
{
    if (bUseShader)
        this->Use();
    glUniform2f(glGetUniformLocation(this->ID_, name), x, y);
}
void Shader::setVector2f(const char *name, const glm::vec2 &value, bool bUseShader)
{
    if (bUseShader)
        this->Use();
    glUniform2f(glGetUniformLocation(this->ID_, name), value.x, value.y);
}
void Shader::setVector3f(const char *name, float x, float y, float z, bool bUseShader)
{
    if (bUseShader)
        this->Use();
    glUniform3f(glGetUniformLocation(this->ID_, name), x, y, z);
}
void Shader::setVector3f(const char *name, const glm::vec3 &value, bool bUseShader)
{
    if (bUseShader)
        this->Use();
    glUniform3f(glGetUniformLocation(this->ID_, name), value.x, value.y, value.z);
}
void Shader::setVector4f(const char *name, float x, float y, float z, float w, bool bUseShader)
{
    if (bUseShader)
        this->Use();
    glUniform4f(glGetUniformLocation(this->ID_, name), x, y, z, w);
}
void Shader::setVector4f(const char *name, const glm::vec4 &value, bool bUseShader)
{
    if (bUseShader)
        this->Use();
    glUniform4f(glGetUniformLocation(this->ID_, name), value.x, value.y, value.z, value.w);
}
void Shader::setMat4(const char *name, const glm::mat4 &matrix, bool bUseShader)
{
    if (bUseShader)
        this->Use();
    glUniformMatrix4fv(glGetUniformLocation(this->ID_, name), 1, false, glm::value_ptr(matrix));
}


void Shader::checkCompileErrors(unsigned int object, std::string type)
{
    int success;
    char infoLog[1024];
    if (type != "PROGRAM")
    {
        glGetShaderiv(object, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(object, 1024, NULL, infoLog);
            std::cout << "| ERROR::SHADER: Compile-time error: Type: " << type << "\n"
                << infoLog << "\n -- --------------------------------------------------- -- "
                << std::endl;
        }
    }
    else
    {
        glGetProgramiv(object, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(object, 1024, NULL, infoLog);
            std::cout << "| ERROR::Shader: Link-time error: Type: " << type << "\n"
                << infoLog << "\n -- --------------------------------------------------- -- "
                << std::endl;
        }
    }
}