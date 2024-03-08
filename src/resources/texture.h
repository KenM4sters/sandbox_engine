#pragma once
#include "../utils/includes.h"

/**
 * Much like the Shader class, the Texture2D class is reponsible generating and binding data,
 * in this case texture data, that is stored in an unordered_map held by the resource class.
 * Texture data first needs to be generated from an image url which is handled by the single-header
 * file "stb_image.h", and then configured as a texture using the OpenGL api.
 * 
 * Finally, the texture needs to be bound when attempting to make a draw call to whichever object,
 * or in our case "Mesh", the texture is intended for.
 *  
 * An important part of using textures in OpenGL is that textures need to be instructed of how
 * they're meant to be placed on objects, which is determined by a set if coordinates known as
 * "texture coordinates", often abbreviated to "text_coords" throughout this program.
 * 
 * These coordinates map points on the geometry to points on the texture, allowing the user to decide
 * where they want the texture to be placed. These texture coords should be passed to the GPU through
 * Mesh::Geometry::AddBufferAttribute(), and accessed in the shader prgrams themselves to be used.
*/
class Texture2D
{
public:
    unsigned int ID_; // ID_ is used as a key for each texture data in the Resources' texture map. 
    unsigned int width_, height_; // In px.
    unsigned int internal_format_;
    unsigned int image_format_; 
    unsigned int wrap_s_; // Not necessary.
    unsigned int wrap_t_; // Not necessary.
    unsigned int filter_min_; 
    unsigned int filter_max_; 

    Texture2D();

    // Uses texture data generated from the Resource class using stb_image.h to configure the texture
    // using OpenGL specfic functions, so that they can be used as actual textures. 
    void Generate(unsigned int width, unsigned int height, unsigned char* data);

    // Similar to Shader::Use() only for textures instead - binds the texture so that any 
    // draw calls that follow will assume the currently bounded texture, therefore each different
    // texture must be bound at the time of drawing the "Mesh" that it belongs to.
    void Bind() const;
};
