#pragma once
// #define SANDBOX_DEBUG
// Engine 
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

// STL
#include <iostream>
#include <stdlib.h>
#include <vector>
#include <map>
#include <string>
#include <cassert>


#define SANDBOX_OBJECT 0xff0000
#define SANDBOX_LIGHT 0x00ff00
#define SANDBOX_INSTANCED 0x00000f
#define SANDBOX_TRIANGLE                  0
#define SANDBOX_SQUARE                    1
#define SANDBOX_CUBE                      3
#define SANDBOX_DEFAULT_STRIDE            3*sizeof(float)
#define SANDBOX_DEFAULT_OFFEST            (void*)0
#define SANDBOX_TRIANGLE_VERTICES_COUNT   3
#define SANDBOX_SQUARE_VERTICES_COUNT     6
#define SANDBOX_CUBE_VERTICES_COUNT       36
#define SANDBOX_TRIANGLE_VERTICES         {-0.5f, -0.5f, 0.0f, 0.5f, -0.5f, 0.0f, 0.0f, 0.5f, 0.0f}
#define SANDBOX_SQUARE_VERTICES           {0.5f,  0.5f, 0.0f, 0.5f, -0.5f, 0.0f, -0.5f, 0.5f, 0.0f, 0.5f, -0.5f, 0.0f, -0.5f, -0.5f, 0.0f, -0.5f, 0.5f, 0.0f}
#define SANDBOX_SQUARE_NORMAL_COORDS      {0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f}
#define SANDBOX_SQUARE_TEX_COORDS         {0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f}
#define SANDBOX_CUBE_VERTICES             {\
                                            -0.5f, -0.5f, -0.5f, \
                                            0.5f, -0.5f, -0.5f, \
                                            0.5f,  0.5f, -0.5f,\
                                            0.5f,  0.5f, -0.5f,\
                                            -0.5f,  0.5f, -0.5f,\
                                            -0.5f, -0.5f, -0.5f,\
                                            -0.5f, -0.5f,  0.5f,\
                                            0.5f, -0.5f,  0.5f,\
                                            0.5f,  0.5f,  0.5f,\
                                            0.5f,  0.5f,  0.5f,\
                                            -0.5f,  0.5f,  0.5f,\
                                            -0.5f, -0.5f,  0.5f,\
                                            -0.5f,  0.5f,  0.5f,\
                                            -0.5f,  0.5f, -0.5f,\
                                            -0.5f, -0.5f, -0.5f,\
                                            -0.5f, -0.5f, -0.5f,\
                                            -0.5f, -0.5f,  0.5f,\
                                            -0.5f,  0.5f,  0.5f,\
                                            0.5f,  0.5f,  0.5f,\
                                            0.5f,  0.5f, -0.5f,\
                                            0.5f, -0.5f, -0.5f,\
                                            0.5f, -0.5f, -0.5f,\
                                            0.5f, -0.5f,  0.5f,\
                                            0.5f,  0.5f,  0.5f,\
                                            -0.5f, -0.5f, -0.5f,\
                                            0.5f, -0.5f, -0.5f,\
                                            0.5f, -0.5f,  0.5f,\
                                            0.5f, -0.5f,  0.5f,\
                                            -0.5f, -0.5f,  0.5f,\
                                            -0.5f, -0.5f, -0.5f,\
                                            -0.5f,  0.5f, -0.5f,\
                                            0.5f,  0.5f, -0.5f,\
                                            0.5f,  0.5f,  0.5f,\
                                            0.5f,  0.5f,  0.5f,\
                                            -0.5f,  0.5f,  0.5f,\
                                            -0.5f,  0.5f, -0.5f\
                                          }
#define SANDBOX_CUBE_NORMAL_COORDS        {\
                                            0.0f,  0.0f, -1.0f, \
                                            0.0f,  0.0f, -1.0f,\
                                            0.0f,  0.0f, -1.0f,\
                                            0.0f,  0.0f, -1.0f,\
                                            0.0f,  0.0f, -1.0f,\
                                            0.0f,  0.0f, -1.0f,\
                                            0.0f,  0.0f, 1.0f,\
                                            0.0f,  0.0f, 1.0f,\
                                            0.0f,  0.0f, 1.0f,\
                                            0.0f,  0.0f, 1.0f,\
                                            0.0f,  0.0f, 1.0f,\
                                            0.0f,  0.0f, 1.0f,\
                                            -1.0f,  0.0f,  0.0f,\
                                            -1.0f,  0.0f,  0.0f,\
                                            -1.0f,  0.0f,  0.0f,\
                                            -1.0f,  0.0f,  0.0f,\
                                            -1.0f,  0.0f,  0.0f,\
                                            -1.0f,  0.0f,  0.0f,\
                                            1.0f,  0.0f,  0.0f,\
                                            1.0f,  0.0f,  0.0f,\
                                            1.0f,  0.0f,  0.0f,\
                                            1.0f,  0.0f,  0.0f,\
                                            1.0f,  0.0f,  0.0f,\
                                            1.0f,  0.0f,  0.0f,\
                                            0.0f, -1.0f,  0.0f,\
                                            0.0f, -1.0f,  0.0f,\
                                            0.0f, -1.0f,  0.0f,\
                                            0.0f, -1.0f,  0.0f,\
                                            0.0f, -1.0f,  0.0f,\
                                            0.0f, -1.0f,  0.0f,\
                                            0.0f,  1.0f,  0.0f,\
                                            0.0f,  1.0f,  0.0f,\
                                            0.0f,  1.0f,  0.0f,\
                                            0.0f,  1.0f,  0.0f,\
                                            0.0f,  1.0f,  0.0f,\
                                            0.0f,  1.0f,  0.0f\
                                          }
#define SANDBOX_CUBE_TEX_COORDS           {\
                                            0.0f,  0.0f,\
                                            1.0f,  0.0f,\
                                            1.0f,  1.0f,\
                                            1.0f,  1.0f,\
                                            0.0f,  1.0f,\
                                            0.0f,  0.0f,\
                                            0.0f,  0.0f,\
                                            1.0f,  0.0f,\
                                            1.0f,  1.0f,\
                                            1.0f,  1.0f,\
                                            0.0f,  1.0f,\
                                            0.0f,  0.0f,\
                                            1.0f,  0.0f,\
                                            1.0f,  1.0f,\
                                            0.0f,  1.0f,\
                                            0.0f,  1.0f,\
                                            0.0f,  0.0f,\
                                            1.0f,  0.0f,\
                                            1.0f,  0.0f,\
                                            1.0f,  1.0f,\
                                            0.0f,  1.0f,\
                                            0.0f,  1.0f,\
                                            0.0f,  0.0f,\
                                            1.0f,  0.0f,\
                                            0.0f,  1.0f,\
                                            1.0f,  1.0f,\
                                            1.0f,  0.0f,\
                                            1.0f,  0.0f,\
                                            0.0f,  0.0f,\
                                            0.0f,  1.0f,\
                                            0.0f,  1.0f,\
                                            1.0f,  1.0f,\
                                            1.0f,  0.0f,\
                                            1.0f,  0.0f,\
                                            0.0f,  0.0f,\
                                            0.0f,  1.0f\
                                          }
    const std::vector<float> cube_vertices = {
      //  back
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
      // front
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
      // left
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
        -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
      // right
         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
         0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
      // bottom
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
      // top
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f
    };

    const std::vector<float> square_vertices = {
        0.5f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f,   1.0f, 1.0f,  
        0.5f, -0.5f, 0.0f,  0.0f, 0.0f, 1.0f,   1.0f, 0.0f,   
       -0.5f, -0.5f, 0.0f,  0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   
       -0.5f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f,   0.0f, -1.0f  
    };
    const std::vector<unsigned int> square_indices = {
        0, 1, 3,   
        1, 2, 3 
    };

