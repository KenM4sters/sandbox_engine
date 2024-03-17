#include "buffer_geometry.h"


BufferGeometry::BufferGeometry(const std::vector<float> &vertices, unsigned int vertex_count) :
    vertex_count_(vertex_count), vertices_float(vertices)
{
    glGenBuffers(1, &VBO_);
    glGenVertexArrays(1, &VAO_);
    glBindVertexArray(VAO_);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_);
    glBufferData(GL_ARRAY_BUFFER, vertices_float.size() * sizeof(float), vertices_float.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void*)(0));
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void*)(3*sizeof(float)));
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void*)(6*sizeof(float)));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

BufferGeometry::BufferGeometry(const std::vector<float> &vertices, const std::vector<unsigned int> &indices, unsigned int vertex_count) 
    : vertices_float(vertices), indices_(indices), vertex_count_(vertex_count)
{
    glGenBuffers(1, &VBO_);
    glGenVertexArrays(1, &VAO_);
    glGenBuffers(1, &EBO_);
    glBindVertexArray(VAO_);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_);
    glBufferData(GL_ARRAY_BUFFER, vertices_float.size() * sizeof(float), vertices_float.data(), GL_STATIC_DRAW);
    // Indices
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices_.size()*sizeof(unsigned int), indices_.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void*)(0));
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void*)(3*sizeof(float)));
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void*)(6*sizeof(float)));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);

    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

BufferGeometry::BufferGeometry(const std::vector<float> &vertices, const std::vector<unsigned int> &indices, std::vector<float> &instance_positions)
    : vertices_float(vertices), indices_(indices), instance_count_(instance_positions.size() / 3)
{
    glGenBuffers(1, &VBO_);
    glGenVertexArrays(1, &VAO_);
    glGenBuffers(1, &EBO_);
    glBindVertexArray(VAO_);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_);
    glBufferData(GL_ARRAY_BUFFER, vertices_float.size() * sizeof(float), vertices_float.data(), GL_STATIC_DRAW);
    // Indices
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices_.size()*sizeof(unsigned int), indices_.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void*)(0));
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void*)(3*sizeof(float)));
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void*)(6*sizeof(float)));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);

    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    std::cout << "Instance geometry created" << std::endl;
    // Instacing
    unsigned int instance_VBO;
    glGenBuffers(1, &instance_VBO);
    glBindVertexArray(VAO_);
    glBindBuffer(GL_ARRAY_BUFFER, instance_VBO);
    glBufferData(GL_ARRAY_BUFFER, instance_positions.size() * sizeof(float), instance_positions.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, (void*)(0));
    glEnableVertexAttribArray(3);
    glVertexAttribDivisor(3, 1);
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void BufferGeometry::InitGeometry() {
    glGenBuffers(1, &VBO_);
    glGenBuffers(1, &EBO_);
    glGenVertexArrays(1, &VAO_);
    glBindVertexArray(VAO_);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_);
    glBufferData(GL_ARRAY_BUFFER, vertices_vertex.size()*sizeof(Vertex), vertices_vertex.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices_.size()*sizeof(unsigned int), indices_.data(), GL_STATIC_DRAW);
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(0));
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(offsetof(Vertex, normal)));
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(offsetof(Vertex, tex_coords)));
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(offsetof(Vertex, tangent)));
    glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(offsetof(Vertex, bi_tangent)));
    glVertexAttribPointer(5, 1, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(offsetof(Vertex, texel_val)));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
    glEnableVertexAttribArray(3);
    glEnableVertexAttribArray(4);
    glEnableVertexAttribArray(5);

    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void BufferGeometry::DrawGeometry() {
    glBindVertexArray(VAO_);
    if(!indices_.empty()) {
        glDrawElements(GL_TRIANGLES, static_cast<unsigned int>(indices_.size()), GL_UNSIGNED_INT, 0);
    } else {
        glDrawArrays(GL_TRIANGLES, 0, vertex_count_);
    }
    glBindVertexArray(0);
}

void BufferGeometry::DrawGeometry(unsigned int n_strips, unsigned int n_vertices_strip) {
    glBindVertexArray(VAO_);
    for(unsigned int i = 0; i < n_strips; i++) {
        glDrawElements(
            GL_TRIANGLE_STRIP, 
            n_vertices_strip, 
            GL_UNSIGNED_INT, 
            (void*)(sizeof(unsigned int)*n_vertices_strip*i)
        );
    }
    glBindVertexArray(0);
}

void BufferGeometry::DrawGeometryInstanced(unsigned int instance_count) {
    // isntance_count_ is initially inferred and set from the size of the vertices that you pass into the constructor,
    // but if you chose to specify a count in this draw function, then the instance_count_ will be set to that.
    if(instance_count != 0) {
        instance_count_ = instance_count;
    }
    glBindVertexArray(VAO_);
    if(!indices_.empty()) { 
        glDrawElementsInstanced(GL_TRIANGLES, static_cast<unsigned int>(indices_.size()), GL_UNSIGNED_INT, 0, instance_count_);
    } else {
        glDrawArraysInstanced(GL_TRIANGLES, 0, vertex_count_, instance_count_);
    }
    glBindVertexArray(0);
}

// TODO
std::vector<Vertex> MakeVertexFromVector(std::vector<float> &data) {
    const auto size = data.size();
    if(size % 20 != 0) throw std::runtime_error("Vertex data must be a multiple of 20 to be converted to a Vertex");
    std::vector<Vertex> vertices;
    for(unsigned int i = 0; i < vertices.size() / 20; i++) {
        Vertex v;
        v.position = glm::vec3{data[i], data[i + 1], data[i + 2]};
        v.normal = glm::vec3{data[i + 3], data[i + 4], data[i + 5]};
        v.tex_coords = glm::vec2{data[i + 6], data[i + 7]};
    }
    return vertices;
}