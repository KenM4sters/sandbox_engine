#pragma once
#include "../standard_mesh.h"
#include "../../resources/stb_image.h"
#define TERRRAIN_QUADRANTS_SIZE 16

struct TerrainQuadrant {
    std::vector<Vertex> vertices;
    glm::vec3 center_vert;
    glm::vec3 left, right, top, bottom;
};

class Terrain {
    public:
        Terrain(const char* height_map, Shader* shader, Texture2D* tex, unsigned int &scale) 
            : y_scale_(scale), shader_(shader), tex_(tex) 
        {
            int width, height, nr_channels;
            unsigned char* data = stbi_load(height_map, &width, &height, &nr_channels, 0);
            if(data == nullptr) 
                throw std::runtime_error("Couldn't load terrain height map");
            width_ = width;
            depth_ = height;
            InitTerrainMeshData(data, width, height, nr_channels);
            transforms_.position = {0.0f, -20.0f, 0.0f};
        }
        ~Terrain() {}
        void DrawTerrain();
        void InitTerrainMeshData(unsigned char* data, int &width, int &height, int &nr_channels);
        BufferGeometry* geometry_;
        Transforms transforms_;
        int width_;
        int depth_;
        std::vector<Vertex> vertices_;
        std::unordered_map<std::string, TerrainQuadrant> terrain_quadrants_;
    private:
        void GenerateTerrainQuadrants();
        unsigned int y_scale_;
        Shader* shader_;
        Texture2D* tex_;
        Material mat_;
        unsigned int n_strips_;
        unsigned int n_vertices_strip_;
        std::vector<unsigned int> indices_;
        
};