#include "Screens.h"

#include <cstdio>
#include <cstdlib>

#include "../core/App.h"
#include "../core/Console.h"

namespace car {

void SettingsScreen::render(App& app) {
    Settings& s = app.settings();
    printf("  [1] Volume      : %d\n", s.volume());
    printf("  [2] Theme       : %s\n", s.themeName().c_str());
    printf("  [3] Units       : %s\n", s.unitName().c_str());
    printf("  [4] Language    : %s\n", s.language().c_str());
    printf("  [5] Shuffle     : %s\n\n", s.shuffle() ? "on" : "off");
    console::hint("number = change, '1 60' = set volume directly, b = back");
}

void SettingsScreen::handleInput(App& app, const std::string& input) {
    Settings& s = app.settings();

    // "1 60" sets the volume in one go; a bare "1" prompts for the value.
    if (input.size() > 2 && input[0] == '1' && input[1] == ' ') {
        s.setVolume(std::atoi(input.c_str() + 2));
        app.setStatus("Volume " + std::to_string(s.volume()));
        return;
    }

    size_t index = 0;
    if (!console::parseIndex(input, 5, index)) {
        app.setStatus("Unknown setting: " + input);
        return;
    }

    switch (index) {
        case 0: {
            std::string value;
            if (console::readLine("  New volume (0-100): ", value)) {
                s.setVolume(std::atoi(value.c_str()));
                app.setStatus("Volume " + std::to_string(s.volume()));
            }
            break;
        }
        case 1: s.toggleTheme();    app.setStatus("Theme " + s.themeName()); break;
        case 2: s.toggleUnits();    app.setStatus("Units " + s.unitName()); break;
        case 3: s.cycleLanguage();  app.setStatus("Language " + s.language()); break;
        case 4: s.toggleShuffle();  app.setStatus(std::string("Shuffle ") + (s.shuffle() ? "on" : "off")); break;
    }
}

} // namespace car
