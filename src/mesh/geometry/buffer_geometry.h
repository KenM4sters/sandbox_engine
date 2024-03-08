#pragma once
#include "../../utils/includes.h"
#define SANDBOX_TRIANGLE                  0
#define SANDBOX_SQUARE                    1
#define SANDBOX_CUBE                      3
#define SANDBOX_DEFAULT_STRIDE            3*sizeof(float)
#define SANDBOX_DEFAULT_OFFEST            (void*)0
#define SANDBOX_TRIANGLE_VERTICES_COUNT   3;
#define SANDBOX_SQUARE_VERTICES_COUNT     6;
#define SANDBOX_CUBE_VERTICES_COUNT       36;
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

                                          
class BufferAtrribute {
    public:
        BufferAtrribute(std::vector<float> vertices, unsigned int count)
             : vertices_(vertices), count_(count) {}
        
        // Returns the vertices and count of a buffer attribute as a pair.
        std::pair<std::vector<float>, unsigned int> GetData() const {
            return std::pair<std::vector<float>, unsigned int>(vertices_, count_);
        }

    private:
        std::vector<float> vertices_;
        unsigned int count_;
};

class UBufferGeometry {
    public:
        // type = SANDBOX_TRIANGLE || SANDBOX_SQUARE || SANDBOX_CUBE
        UBufferGeometry(unsigned int type = SANDBOX_TRIANGLE) : type_(type) {
            initGeometry();
        }
        void AddBufferAttribute(std::string name, unsigned int loc, BufferAtrribute* attribute) {
            attributes_[name] = std::pair<BufferAtrribute*, unsigned int>(attribute, loc);
        }

        // Returns the address of the buffer attributes map.
        const std::unordered_map<std::string, std::pair<BufferAtrribute*, unsigned int>>* GetAttributes() {
            return &attributes_;
        }

        unsigned int type_, vert_count_;

    private:
        std::unordered_map<std::string, std::pair<BufferAtrribute*, unsigned int>> attributes_;
        void initGeometry() {
            std::vector<float> vertices = SANDBOX_TRIANGLE_VERTICES;
            switch(type_) {
                case SANDBOX_TRIANGLE:  
                    vert_count_ = SANDBOX_TRIANGLE_VERTICES_COUNT;
                    vertices = SANDBOX_TRIANGLE_VERTICES;
                    break;
                case SANDBOX_SQUARE:  
                    vert_count_ = SANDBOX_SQUARE_VERTICES_COUNT;
                    vertices = SANDBOX_SQUARE_VERTICES;
                    break;
                case SANDBOX_CUBE:  
                    vert_count_ = SANDBOX_CUBE_VERTICES_COUNT;
                    vertices = SANDBOX_CUBE_VERTICES;
                    break;
            }

            AddBufferAttribute("position", 0, new BufferAtrribute(vertices, 3));
        }
};