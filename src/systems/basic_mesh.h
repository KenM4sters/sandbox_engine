#pragma once
#include "mesh.h"

/**
 * The BasicMesh class is plays a fundamental role in provide an easy to use format of displaying 
 * objects in our scene. Much like its sister class, StandardMesh, the BasicMesh class is responsible
 * for allocating memory for geometry vertex data, and making the appropriate draw calls to render
 * those objects to the scene. 
*/

class BasicMesh : public UMesh<float> {
    public:
        // Simplified constructor which only takes in single texture
        BasicMesh(BufferGeometry* geometry, Shader* shader, Texture2D* texture)
            : geometry_(geometry) 
        {
            shader_ = shader;
            mat_.textures.push_back(texture);
        }
        // Constructor for binding multiple textures to a shader program
        BasicMesh(BufferGeometry* geometry, Shader* shader, std::vector<Texture2D*> &textures)
            : geometry_(geometry) 
        {
            shader_ = shader;
            mat_.textures = textures;
        }
        ~BasicMesh() {}
        // Sets uniform data, binds textures and shaders, and calls the geometry::Draw() method to handle
        // VAO binding and calling OpenGL draw calls. 
        void Draw(float &delta_time) override;
        // Similar to Draw, only it takes in an extra parameter which defines how many insances of the same
        // geometry a user would like to render, and calls geometry::DrawInstanced() which handles rendering
        // to accomodate for the new instance data. 
        void DrawInstanced(float &delta_time, unsigned int instance_count = 0) override;
        // Instantiates a new BoundingBox object - please see bounding_box.h for more details. 
        void ComputeBoundingBox(Shader* shader, float vertices_data = 0.0f) override;

        // The Material struct hold a texture vector as well as glm::vec3s to store shading properties
        // which define how the material interacts with lights.  
        Material mat_;
    private:
        // Please see buffer_geometry.h for details.
        BufferGeometry* geometry_;
};