#include "collision_handler.h"


void CollisionHandler::FeedObjects(std::unordered_map<std::string, BasicMesh*> &objects) {
    for(const auto &obj : objects) {
        b_objects_.insert(obj);
    }
}
void CollisionHandler::FeedObjects(std::unordered_map<std::string, Model*> &objects) {
    for(const auto &obj : objects) {
        models_.insert(obj);
    }
}
void CollisionHandler::FeedTerrain(Terrain* terrain) {
    terrain_ = terrain;

    // int left = 0;
    // int name_counter = 1;
    // int right = v.size() / TERRRAIN_QUADRANTS_SIZE;
    // while(right <= v.size()) {
    //     std::vector<Vertex> vertices;
    //     std::vector<Vertex>::iterator itr;
    //     itr = vertices.begin();
    //     vertices.insert(itr, v.begin() + left, v.begin() + right);
    //     terrain_quadrants_["quad_" + std::to_string(name_counter)];
    //     name_counter++;
    //     left = right;
    //     right += v.size()/ TERRRAIN_QUADRANTS_SIZE;
    // }

}

void CollisionHandler::CheckCollisions() {
    
}

void CollisionHandler::ManageCollision() {

}
