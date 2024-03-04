#include "app.h"

// Implementation for main app

sandbox_app::App::App(const std::string& app_name) {
    window_ = std::make_unique<sandbox_window::SWindow>();
    window_->init(800, 600, app_name);
}

void sandbox_app::App::loop() {
    window_->render();
}