#pragma once
#include "utils/includes.h"
#include "s_window.h"

// Entry point for entire application. The loop() funciton is main game loop that calls the Draw() functions
// of each of its members.
class App {
    public:
        App(const std::string& app_name);
        void loop();
    private:
        std::unique_ptr<SWindow> window_;
};
