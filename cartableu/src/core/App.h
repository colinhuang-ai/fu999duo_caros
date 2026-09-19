#pragma once
#include <memory>
#include <string>
#include <vector>

#include "Screen.h"
#include "../services/MapService.h"
#include "../services/MusicLibrary.h"
#include "../services/Settings.h"

namespace car {

// Owns the services and the screen stack, and runs the input loop.
class App {
public:
    App();

    void run();

    void push(std::unique_ptr<Screen> screen);
    // pop()/popToHome() are deferred to the end of the input dispatch so a
    // screen can close itself from inside its own handleInput().
    void pop();
    void popToHome();
    void quit() { running_ = false; }

    // Shown once under the next render, then cleared.
    void setStatus(const std::string& text) { status_ = text; }

    MusicLibrary& music() { return music_; }
    MapService& maps() { return maps_; }
    Settings& settings() { return settings_; }

    // Currently playing track, or nullptr when the player is idle.
    const Song* nowPlaying() const { return nowPlaying_; }
    void setNowPlaying(const Song* song) { nowPlaying_ = song; }

private:
    Screen& top() { return *screens_.back(); }
    void drawStatusBar();
    void applyPendingNavigation();
    void flushStatus();

    std::vector<std::unique_ptr<Screen>> screens_;
    MusicLibrary music_;
    MapService maps_;
    Settings settings_;
    const Song* nowPlaying_ = nullptr;
    std::string status_;
    int pendingPops_ = 0;
    bool pendingHome_ = false;
    bool running_ = true;
};

} // namespace car
