#include "Screens.h"

#include <cstdio>
#include <memory>

#include "../core/App.h"
#include "../core/Console.h"

namespace car {

void MusicScreen::render(App& app) {
    const MusicLibrary& lib = app.music();
    for (size_t i = 0; i < lib.size(); ++i) {
        const Song& s = lib.at(i);
        const bool playing = app.nowPlaying() == &s;
        printf("  [%zu] %-26s %-18s %6s %s\n", i + 1, s.title.c_str(), s.artist.c_str(),
               formatDuration(s.durationSec).c_str(), playing ? " <playing" : "");
    }
    printf("\n");
    console::info(std::string("Shuffle: ") + (app.settings().shuffle() ? "on" : "off"));
    printf("\n");
    console::hint("number = play, s = toggle shuffle, b = back");
}

void MusicScreen::handleInput(App& app, const std::string& input) {
    if (input == "s") {
        app.settings().toggleShuffle();
        app.setStatus(std::string("Shuffle ") + (app.settings().shuffle() ? "on" : "off"));
        return;
    }

    size_t index = 0;
    if (!console::parseIndex(input, app.music().size(), index)) {
        app.setStatus("No such track: " + input);
        return;
    }

    const Song& song = app.music().at(index);
    app.setNowPlaying(&song);
    app.push(std::unique_ptr<Screen>(new NowPlayingScreen(song)));
}

} // namespace car
