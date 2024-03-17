#pragma once
#include "../basic_mesh.h"

class Scenery {
    public:
        Scenery(Shader* shader, Material &mat, std::vector<Vertex> instance_vertices)
            : shader_(shader), mat_(mat)
        {
            std::vector<float> instance_positions;
            for(const auto& v : instance_vertices) {
                instance_positions.push_back(v.position.x);
                instance_positions.push_back(v.position.y);
                instance_positions.push_back(v.position.z);
            }
            misc_mesh = new BasicMesh(new BufferGeometry(square_vertices, square_indices, instance_positions), shader_, mat_.textures);
        }
        ~Scenery() {}
        void Draw(float& delta_time);
    private:
        // Optimization - a geometry for both grass and flowers. The fragment shader decides which texture to dra
        // based a few criteria. 
        BasicMesh* misc_mesh;
        Shader* shader_;
        Material mat_;
};