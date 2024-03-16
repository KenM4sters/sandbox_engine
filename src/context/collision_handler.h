#pragma once
#include "../utils/includes.h"
#include "../systems/basic_mesh.h"
#include "../systems/model.h"
#include "../systems/terrain/terrain.h"
#define TERRRAIN_QUADRANTS_SIZE 16

class CollisionHandler {
    public:
        CollisionHandler() {}
        ~CollisionHandler() {}
        void FeedObjects(std::unordered_map<std::string, BasicMesh*> &objects);
        void FeedObjects(std::unordered_map<std::string, Model*> &objects);
        void FeedTerrain(Terrain* terrain);
        void CheckCollisions();
        void ManageCollision();
    private:
        std::unordered_map<std::string, BasicMesh*> b_objects_;
        std::unordered_map<std::string, Model*> models_;
        Terrain* terrain_;
        std::unordered_map<std::string, std::vector<Vertex>> terrain_quadrants_;
};