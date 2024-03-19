#pragma once
#include "../../resources/stb_image.h"
#include "../../resources/s_texture_resource.h"
#include "../standard_mesh.h"
#include "../system_includes.h"
#include "scenery.h"

/**
 * The Terrain class completely handles setting and allocating memory for its vertex data, generating and
 * rendering its scenery object as well as itself.
*/

class Terrain {
    public:
        Terrain(const char* height_map, Shader* shader, Material &mat, unsigned int &scale) 
            : y_scale_(scale), shader_(shader), mat_(mat) 
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
        void DrawTerrain(float& delta_time);
        void InitTerrainMeshData(unsigned char* data, int &width, int &height, int &nr_channels);
        void GenerateScenary(Shader* shader, Material &scenery_mat);
        BufferGeometry* geometry_;
        Transforms transforms_;
        int width_;
        int depth_;
        std::vector<Vertex> vertices_;
        std::unordered_map<std::string, VertexQuadrant> terrain_quadrants_;
        Scenery* scenery;
    private:
        void GenerateTerrainNormals();
        void GenerateTerrainQuadrants(unsigned int base_num);
        unsigned int y_scale_;
        Shader* shader_;
        STextureResource ground_textures_;
        Material mat_;
        unsigned int n_strips_;
        unsigned int n_vertices_strip_;
        std::vector<unsigned int> indices_;
        
};