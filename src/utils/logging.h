#pragma once
#include "../mesh/mesh.h"
#include "../mesh/geometry/buffer_geometry.h"

class Logger {
    public:
        Logger() {}
        static void LogMesh(unsigned int type, unsigned int stride, unsigned int vert_count, void* offset) {
                std::cout << "-----------------------------" << std::endl;
                std::cout << "SUCCESS::Mesh initialized!" << std::endl;
                std::cout << "-----------------------------" << std::endl;
                std::cout << "Type: " << type << std::endl;
                std::cout << "Size: " << vert_count * 12 << std::endl;
                std::cout << "Stride: " << stride << std::endl;
                std::cout << "Offset: " << offset << std::endl;
                std::cout << "Vertices Count: " << vert_count << std::endl;
                std::cout << "-----------------------------" << std::endl;
        }
        static void LogAttributes(std::string material_nane, unsigned int type, unsigned int data_size, 
                unsigned int stride, unsigned int offset) 
        {
                std::cout << "-----------------------------" << std::endl;
                std::cout << "SUCCESS::Buffer Attribute Added!" << std::endl;
                std::cout << "-----------------------------" << std::endl;
                std::cout << "Material: " << material_nane << std::endl;
                std::cout << "Type: " << type << std::endl;
                std::cout << "Size: " << data_size << std::endl;
                std::cout << "Stride: " << stride << std::endl;
                std::cout << "Offset: " << offset << std::endl;
                std::cout << "-----------------------------" << std::endl;
        }
};