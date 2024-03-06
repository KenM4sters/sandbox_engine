#pragma once
#include "../mesh/mesh.h"
#include "../mesh/geometry/buffer_geometry.h"

class Logger {
    public:
        Logger() {}
        static void LogGeometry(unsigned int type, unsigned int stride, unsigned int vert_count, void* offset) {
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
};