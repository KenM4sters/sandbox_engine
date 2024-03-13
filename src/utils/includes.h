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
                                          }\

