#include "App.h"

#include <iostream>

#include "Console.h"
#include "../screens/Screens.h"

namespace car {

App::App() { screens_.push_back(std::unique_ptr<Screen>(new HomeScreen())); }

void App::push(std::unique_ptr<Screen> screen) { screens_.push_back(std::move(screen)); }

void App::pop() {
    if (screens_.size() > static_cast<size_t>(pendingPops_) + 1) {
        ++pendingPops_;
    } else {
        setStatus("Already on the home screen.");
    }
}

void App::popToHome() { pendingHome_ = true; }

void App::applyPendingNavigation() {
    if (pendingHome_) {
        while (screens_.size() > 1) screens_.pop_back();
    } else {
        while (pendingPops_ > 0 && screens_.size() > 1) {
            screens_.pop_back();
            --pendingPops_;
        }
    }
    pendingPops_ = 0;
    pendingHome_ = false;
}

void App::drawStatusBar() {
    std::string bar = "VOL " + std::to_string(settings_.volume()) + "  |  " + settings_.themeName() +
                      "  |  " + settings_.unitName();
    if (nowPlaying_) bar += "  |  > " + nowPlaying_->title;
    console::header(top().title(), bar);
}

void App::flushStatus() {
    if (status_.empty()) return;
    console::info(">> " + status_);
    std::cout << "\n";
    status_.clear();
}

void App::run() {
    while (running_) {
        drawStatusBar();
        top().render(*this);
        flushStatus();

        std::string input;
        if (!console::readLine("  > ", input)) break;  // stdin closed

        if (input.empty()) continue;
        if (input == "q" || input == "quit") { quit(); continue; }
        if (input == "b" || input == "back") { pop(); applyPendingNavigation(); continue; }
        if (input == "h" || input == "home") { popToHome(); applyPendingNavigation(); continue; }

        top().handleInput(*this, input);
        applyPendingNavigation();
    }

    console::clear();
    std::cout << "\n  Head unit off. Drive safe.\n\n";
}

} // namespace car
