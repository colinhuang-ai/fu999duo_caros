#include "Screens.h"

#include <memory>

#include "../core/App.h"
#include "../core/Console.h"

namespace car {

void HomeScreen::render(App& app) {
    console::menu({"Music", "Map", "Settings"});
    
    // If a song is currently playing, show it at the bottom of the screen.
    if (app.nowPlaying()) {
        console::info("Resume: " + app.nowPlaying()->title + " - " + app.nowPlaying()->artist);
    }
    console::hint("type a number, or q to power off");
}

void HomeScreen::handleInput(App& app, const std::string& input) {
    size_t index = 0;
    if (!console::parseIndex(input, 3, index)) {
        app.setStatus("Unknown command: " + input);
        return;
    }
    switch (index) {
        case 0: app.push(std::unique_ptr<Screen>(new MusicScreen())); break;
        case 1: app.push(std::unique_ptr<Screen>(new MapScreen())); break;
        case 2: app.push(std::unique_ptr<Screen>(new SettingsScreen())); break;
    }
}

} // namespace car
