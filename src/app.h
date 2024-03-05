#pragma once
#include "utils/includes.h"
#include "s_window.h"

// Header for main app
class App {
    public:
        App(const std::string& app_name);
        void loop();
    private:
        std::unique_ptr<SWindow> window_;
};
