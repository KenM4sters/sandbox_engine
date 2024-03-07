#pragma once
#include "../../utils/includes.h"
#define SANDBOX_TRIANGLE                  0
#define SANDBOX_SQUARE                    1
#define SANDBOX_CUBE                      3
#define SADNBOX_DEFAULT_STRIDE            3*sizeof(float)
#define SANDBOX_DEFAULT_OFFEST            (void*)0
#define SANDBOX_TRIANGLE_VERTICES_COUNT   3;
#define SANDBOX_SQUARE_VERTICES_COUNT     6;
#define SANDBOX_CUBE_VERTICES_COUNT       36;
#define SANDBOX_TRIANGLE_VERTICES         {-0.5f, -0.5f, 0.0f, 0.5f, -0.5f, 0.0f, 0.0f, 0.5f, 0.0f}
#define SANDBOX_SQUARE_VERTICES           {0.5f,  0.5f, 0.0f, 0.5f, -0.5f, 0.0f, -0.5f, 0.5f, 0.0f, 0.5f, -0.5f, 0.0f, -0.5f, -0.5f, 0.0f, -0.5f, 0.5f, 0.0f}
#define SANDBOX_CUBE_VERTICES              {\
                                            -0.5f, -0.5f, -0.5f,\
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

class BufferAtrribute {
    public:
        BufferAtrribute(std::vector<float> vertices, unsigned int stride)
             : vertices_(vertices), stride_(stride) {}
            
        std::pair<std::vector<float>, unsigned int> GetData() const {
            return std::pair<std::vector<float>, unsigned int>(vertices_, stride_);
        }
        
    private:
        std::vector<float> vertices_;
        unsigned int stride_;
};

class UBufferGeometry {
    public:
        // type = SANDBOX_TRIANGLE || SANDBOX_SQUARE || SANDBOX_CUBE
        UBufferGeometry(unsigned int type = SANDBOX_TRIANGLE) : type_(type) {
            initGeometry();
        }
        void AddBufferAttribute(std::string name, unsigned int loc, BufferAtrribute* attribute) {
            assert(loc != 0 && "ERROR::Buffer attribute must not occupy location 0 - reserved for vertices!");
            attributes_[name] = std::pair<BufferAtrribute*, unsigned int>(attribute, loc);
        }
        const std::unordered_map<std::string, std::pair<BufferAtrribute*, unsigned int>>* GetAttributes() {
            return &attributes_;
        }

        unsigned int type_, stride_, vert_count_;
        std::vector<float> vertices = SANDBOX_TRIANGLE_VERTICES;
        void* offset_;

    private:
        std::unordered_map<std::string, std::pair<BufferAtrribute*, unsigned int>> attributes_;
        void initGeometry() {
            switch(type_) {
                case SANDBOX_TRIANGLE:  
                    stride_ = SADNBOX_DEFAULT_STRIDE;
                    vert_count_ = SANDBOX_TRIANGLE_VERTICES_COUNT;
                    offset_ = SANDBOX_DEFAULT_OFFEST;
                    vertices = SANDBOX_TRIANGLE_VERTICES;
                    break;
                case SANDBOX_SQUARE:  
                    stride_ = SADNBOX_DEFAULT_STRIDE;
                    vert_count_ = SANDBOX_SQUARE_VERTICES_COUNT;
                    offset_ = SANDBOX_DEFAULT_OFFEST;
                    vertices = SANDBOX_SQUARE_VERTICES;
                    break;
                case SANDBOX_CUBE:  
                    stride_ = SADNBOX_DEFAULT_STRIDE;
                    vert_count_ = SANDBOX_CUBE_VERTICES_COUNT;
                    offset_ = SANDBOX_DEFAULT_OFFEST;
                    vertices = SANDBOX_CUBE_VERTICES;
                    break;
            }
        }
};