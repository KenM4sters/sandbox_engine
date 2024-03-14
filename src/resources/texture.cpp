#include "texture.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"


Texture2D::Texture2D(unsigned int sandbox_type, std::string tex_type, const char* path)
    : width_(0), height_(0), format_(GL_RGB), wrap_s_(GL_REPEAT), wrap_t_(GL_REPEAT), filter_min_(GL_LINEAR_MIPMAP_LINEAR), filter_max_(GL_LINEAR)
{
    sandbox_type_ = sandbox_type;
    path_ = path;
    tex_type_ = tex_type;
    glGenTextures(1, &this->ID_);
}

void Texture2D::LoadFromFile(const char* path, std::string &dir) {
    std::string filename = std::string(path);
    filename = dir + '/' + filename;
    int width, height, nrChannels;
    unsigned char *data = stbi_load(filename.c_str(), &width , &height, &nrChannels, 0);
    if (data)
    {
        GLenum format;  
        if (nrChannels == 1)
            format = GL_RED;
        else if (nrChannels == 3)
            format = GL_RGB;
        else if (nrChannels == 4)
            format = GL_RGBA;

        glBindTexture(GL_TEXTURE_2D, this->ID_);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(data);
    }
    else
    {
        std::cout << "Texture failed to load at path: " << path << std::endl;
        stbi_image_free(data);
    }
}

void Texture2D::Generate(unsigned int width, unsigned int height, unsigned char* data)
{
    this->width_ = width;
    this->height_ = height;
    // create Texture
    glBindTexture(GL_TEXTURE_2D, this->ID_);
    glTexImage2D(GL_TEXTURE_2D, 0, this->format_, this->width_, this->height_, 0, this->format_, GL_UNSIGNED_BYTE, data);
    // set Texture wrap and filter modes
    glGenerateMipmap(GL_TEXTURE_2D);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, this->wrap_s_);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, this->wrap_t_);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, this->filter_min_);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, this->filter_max_);
    // unbind texture
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture2D::Bind() const
{
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, this->ID_);
}

void Texture2D::Bind(unsigned int count) const {
    glActiveTexture(GL_TEXTURE0 + count);
    glBindTexture(GL_TEXTURE_2D, this->ID_);
}

void Texture2D::Unbind() const {
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, 0);
}