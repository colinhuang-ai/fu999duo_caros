#include "Screens.h"

#include <cstdio>

#include "../core/App.h"
#include "../core/Console.h"

namespace car {

void MapViewScreen::render(App& app) {
    // zoom 1 shows the whole region, zoom 8 shows just the junction we are on.
    const int rowRadius = 11 - zoom_;
    printf("%s\n", MapService::render(map_, rowRadius, rowRadius * 3).c_str());
    console::info("Legend: A = car, . = road, # = block, P = parking, F = fuel");
    printf("  Zoom %d  |  Position r%d c%d  |  Units %s\n\n", zoom_, map_.carRow, map_.carCol,
           app.settings().unitName().c_str());
    console::hint("w/a/s/d = drive, +/- = zoom, b = back to regions");
}

void MapViewScreen::handleInput(App& app, const std::string& input) {
    int dRow = 0;
    int dCol = 0;
    if (input == "w") dRow = -1;
    else if (input == "s") dRow = 1;
    else if (input == "a") dCol = -1;
    else if (input == "d") dCol = 1;

    if (dRow != 0 || dCol != 0) {
        if (!MapService::move(map_, dRow, dCol)) app.setStatus("Blocked - no road that way.");
        return;
    }

    if (input == "+" || input == "-") {
        zoom_ += (input == "+") ? 1 : -1;
        if (zoom_ < 1) zoom_ = 1;
        if (zoom_ > 8) zoom_ = 8;
        app.setStatus("Zoom " + std::to_string(zoom_));
        return;
    }

    app.setStatus("Unknown control: " + input);
}

} // namespace car
