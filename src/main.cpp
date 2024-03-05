#include "app.h"

int main() {
    auto app = std::make_unique<App>("sandbox_engine");
    app->loop();
    return 0;
}