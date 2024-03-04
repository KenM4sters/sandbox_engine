#pragma once
#include "../utils/includes.h"
#include "../window/s_window.h"

// Header for main app

namespace sandbox_app {
    class App {
        public:
            App(const std::string& app_name);
            ~App() {}

            void loop();
        private:
            std::unique_ptr<sandbox_window::SWindow> window_;
    };
}