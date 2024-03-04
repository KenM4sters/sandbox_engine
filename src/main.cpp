#include "./app/app.h"

int main() {
    auto app = std::make_unique<sandbox_app::App>("sandbox_engine");
    app->loop();
    return 0;
}