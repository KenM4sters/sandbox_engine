#pragma once
#include "../basic_mesh.h"

/**
 * The Scenery class is repsonsible for generating buffer data and making the appropriate draw calls
 * to render miscellaneous scenery objects of our terrain, like grass and flowers. 
*/

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
                instance_positions.push_back(v.position.x + 0.2);
                instance_positions.push_back(v.position.y);
                instance_positions.push_back(v.position.z);
                instance_positions.push_back(v.position.x - 0.2);
                instance_positions.push_back(v.position.y);
                instance_positions.push_back(v.position.z);
                instance_positions.push_back(v.position.x);
                instance_positions.push_back(v.position.y);
                instance_positions.push_back(v.position.z + 0.2);
                instance_positions.push_back(v.position.x);
                instance_positions.push_back(v.position.y);
                instance_positions.push_back(v.position.z - 0.2);
                instance_positions.push_back(v.position.x + 0.3);
                instance_positions.push_back(v.position.y);
                instance_positions.push_back(v.position.z);
                instance_positions.push_back(v.position.x - 0.3);
                instance_positions.push_back(v.position.y);
                instance_positions.push_back(v.position.z);
                instance_positions.push_back(v.position.x);
                instance_positions.push_back(v.position.y);
                instance_positions.push_back(v.position.z + 0.3);
                instance_positions.push_back(v.position.x);
                instance_positions.push_back(v.position.y);
                instance_positions.push_back(v.position.z - 0.3);
            }
            misc_mesh = new BasicMesh(new BufferGeometry(square_vertices, square_indices, instance_positions), shader_, mat_.textures);
            misc_mesh->transforms_.position = glm::vec3(0.0f, 0.5f, 0.0f);
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