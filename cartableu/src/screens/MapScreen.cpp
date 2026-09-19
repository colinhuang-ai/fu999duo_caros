#include "Screens.h"

#include <cstdio>
#include <memory>

#include "../core/App.h"
#include "../core/Console.h"

namespace car {

void MapScreen::render(App& app) {
    const MapService& maps = app.maps();
    for (size_t i = 0; i < maps.size(); ++i) {
        const MapRegion& r = maps.at(i);
        printf("  [%zu] %-30s %s  (%d tiles)\n", i + 1, r.name.c_str(), r.code.c_str(), r.tileCount);
    }
    printf("\n");
    console::hint("number = load that region, b = back");
}

void MapScreen::handleInput(App& app, const std::string& input) {
    size_t index = 0;
    if (!console::parseIndex(input, app.maps().size(), index)) {
        app.setStatus("No such region: " + input);
        return;
    }

    const MapRegion& region = app.maps().at(index);
    console::header("MAP  >  Loading", region.name);
    LoadedMap map = app.maps().load(region);
    console::pause();

    app.setStatus("Map loaded: " + region.name);
    app.push(std::unique_ptr<Screen>(new MapViewScreen(std::move(map))));
}

} // namespace car
