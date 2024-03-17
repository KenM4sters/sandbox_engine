#pragma once
#include "system_includes.h"
#include "../resources/shader.h"
#include "buffer_geometry.h"
#include "../resources/texture.h"
#include "bounding_box.h"

template <typename T>
class UMesh {
    public:
        virtual void Draw(float &delta_time) = 0;
        virtual void DrawInstanced(float &delta_time, unsigned int instance_count = 0) = 0;
        Transforms transforms_;
        Shader* shader_;
        virtual void ComputeBoundingBox(Shader* shader, T vertices_data = {}) = 0;
    protected:
        BoundingBox* bounding_box;
};