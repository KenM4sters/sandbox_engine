#pragma once

#include "../utils/includes.h"

class Texture2D
{
public:
    // holds the ID of the texture object, used for all texture operations to reference to this particular texture
    unsigned int ID;
    unsigned int Width, Height; // in px
    unsigned int Internal_Format;
    unsigned int Image_Format; 
    unsigned int Wrap_S;
    unsigned int Wrap_T; 
    unsigned int Filter_Min; 
    unsigned int Filter_Max; 

    Texture2D();
    // generates texture from image data
    void Generate(unsigned int width, unsigned int height, unsigned char* data);
    // binds the texture as the current active GL_TEXTURE_2D texture object
    void Bind() const;
};
