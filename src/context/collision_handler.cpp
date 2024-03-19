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

}

void CollisionHandler::CheckCollisions() {
    
}

void CollisionHandler::ManageCollision() {

}
