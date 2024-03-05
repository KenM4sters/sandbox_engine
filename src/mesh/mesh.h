#include "material/material.h"
#include "geometry/buffer_geometry.h"
#include "../utils/includes.h"

class Mesh {
    public:
        Mesh(Material* material, BufferGeometry* geometry) : material_(material), geometry_(geometry) {}
        ~Mesh() {}
    private:
        unsigned int VAO_, VBO_;

        Material* material_;
        BufferGeometry* geometry_;

        glm::vec3 scale{1.0f, 1.0f, 1.0f};
        glm::vec3 position{.0f, .0f, .0f};
};