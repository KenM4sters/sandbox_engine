#include "scenery.h"

void Scenery::Draw(float& delta_time) {
    misc_mesh->DrawInstanced(delta_time);
    glUseProgram(0);
}