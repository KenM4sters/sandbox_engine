#include "../utils/includes.h"

class WorldPhysics {
    public:
        static void ApplyGravitationalAcceleration(glm::vec3 &acc_vec) {
            acc_vec.y = -9.81;
        }
    private:
        WorldPhysics() {}
};