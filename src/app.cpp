#include "app.h"

// Implementation for main app
App::App(const std::string& app_name) {
    window_ = std::make_unique<SWindow>(true);
    window_->init(800, 600, app_name);
}

void App::loop() {
    while(window_->isRunning())
        window_->render();
}