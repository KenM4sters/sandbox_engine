#pragma once
#include "../standard_mesh.h"
#include "../../resources/stb_image.h"

class Terrain {
    public:
        Terrain(const char* height_map, Shader* shader, Texture2D* tex, unsigned int &scale) 
            : y_scale_(scale), shader_(shader), tex_(tex) 
        {
            int width, height, nr_channels;
            unsigned char* data = stbi_load(height_map, &width, &height, &nr_channels, 0);
            if(data == nullptr) 
                throw std::runtime_error("Couldn't load terrain height map");
            InitTerrainMeshData(data, width, height, nr_channels);
        }
        ~Terrain() {}
        void DrawTerrain();
        void InitTerrainMeshData(unsigned char* data, int &width, int &height, int &nr_channels);
    private:
        BufferGeometry* geometry_;
        Texture2D* tex_;
        Material mat_;
        Shader* shader_;
        unsigned int y_scale_;
        unsigned int n_strips_;
        unsigned int n_vertices_strip_;
        std::vector<Vertex> vertices_;
        std::vector<unsigned int> indices_;
        
};