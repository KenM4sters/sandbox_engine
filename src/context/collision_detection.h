#pragma once
#include "../utils/includes.h"
#include "../systems/basic_mesh.h"

class CollisionDetector {
    public:
        CollisionDetector() {}
        ~CollisionDetector() {}
        void FeedObjects(std::unordered_map<std::string, BasicMesh*> &objects);
        void CheckCollisions();
        void ManageCollision();
};