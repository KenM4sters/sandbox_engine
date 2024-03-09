#define STB_IMAGE_IMPLEMENTATION
#include "s_texture_resource.h"
#include "stb_image.h"

Texture2D* STextureResource::AddResource(const char* image_url, std::string name, bool bIs_alpha) {
    res_[name] = GenerateTextureDataFromUrl(image_url, bIs_alpha);
    return &res_[name];
}

Texture2D STextureResource::GetResource(std::string name) {
    return res_[name];
}

void STextureResource::DeleteResource(std::string res_name) {
    res_.erase(res_name);
    std::cout << "SUCCESS::" << res_name << "::was succesfullly deleted from texture resource!" << std::endl;
}

void STextureResource::ClearAllResources() {
    for(const auto& tex : res_) {
        glDeleteTextures(GL_TEXTURE_2D, &tex.second.ID_);
    }
}

Texture2D STextureResource::GenerateTextureDataFromUrl(const char* image_url, bool bIs_alpha) {
    Texture2D texture;
    int width, height, nr_channels;
    unsigned char* data = stbi_load(image_url, &width, &height, &nr_channels, 0);
    if(data == nullptr) 
        throw std::runtime_error("ERROR: Failed to load texture data form image path");
    if (nr_channels == 1)
        texture.format_ = GL_RED;
    else if (nr_channels == 3)
        texture.format_ = GL_RGB;
    else if (nr_channels == 4)
        texture.format_ = GL_RGBA;
    texture.Generate(width, height, data);
    // stbi_image_free(data);
    return texture;
}