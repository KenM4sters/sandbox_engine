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
    auto& v = terrain_->vertices_;

    std::vector<Vertex> quad_1;
    std::vector<Vertex>::iterator itr;
    for(int i = 0; i < TERRRAIN_QUADRANTS_SIZE; i++ ) {
        itr = quad_1.begin();
        quad_1.insert(itr, v.begin(), v.begin() + v.size() / 4);
    }


    std::cout << terrain_->world_width_ << std::endl;
    std::cout << terrain_->world_depth_ << std::endl;
}

void CollisionHandler::CheckCollisions() {
    
}

void CollisionHandler::ManageCollision() {

}
