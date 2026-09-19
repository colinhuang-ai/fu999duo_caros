#pragma once
#include <string>
#include <utility>

#include "../core/Screen.h"
#include "../services/MapService.h"
#include "../services/MusicLibrary.h"

namespace car {

class HomeScreen : public Screen {
public:
    std::string title() const override { return "CAR HEAD UNIT"; }
    void render(App& app) override;
    void handleInput(App& app, const std::string& input) override;
};

class MusicScreen : public Screen {
public:
    std::string title() const override { return "MUSIC  >  Library"; }
    void render(App& app) override;
    void handleInput(App& app, const std::string& input) override;
};

class NowPlayingScreen : public Screen {
public:
    explicit NowPlayingScreen(const Song& song) : song_(song) {}
    std::string title() const override { return "MUSIC  >  Now playing"; }
    void render(App& app) override;
    void handleInput(App& app, const std::string& input) override;

private:
    const Song& song_;
    bool paused_ = false;
    int elapsedSec_ = 0;
};

class MapScreen : public Screen {
public:
    std::string title() const override { return "MAP  >  Select region"; }
    void render(App& app) override;
    void handleInput(App& app, const std::string& input) override;
};

class MapViewScreen : public Screen {
public:
    explicit MapViewScreen(LoadedMap map) : map_(std::move(map)) {}
    std::string title() const override { return "MAP  >  " + map_.regionName; }
    void render(App& app) override;
    void handleInput(App& app, const std::string& input) override;

private:
    LoadedMap map_;
    int zoom_ = 3;
};

class SettingsScreen : public Screen {
public:
    std::string title() const override { return "SETTINGS"; }
    void render(App& app) override;
    void handleInput(App& app, const std::string& input) override;
};

} // namespace car
