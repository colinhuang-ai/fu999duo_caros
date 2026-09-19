#include "Screens.h"

#include <cstdio>

#include "../core/App.h"
#include "../core/Console.h"

namespace car {
namespace {

// Text transport bar: 30 cells of elapsed / remaining.
std::string transportBar(int elapsed, int total) {
    const int cells = 30;
    const int filled = total > 0 ? (elapsed * cells) / total : 0;
    std::string bar = "[";
    for (int i = 0; i < cells; ++i) bar += (i < filled) ? '=' : (i == filled ? '>' : '.');
    bar += "]";
    return bar;
}

} // namespace

void NowPlayingScreen::render(App& app) {
    console::info("Title  : " + song_.title);
    console::info("Artist : " + song_.artist);
    console::info(std::string("State  : ") + (paused_ ? "PAUSED" : "PLAYING"));
    printf("\n  %s  %s / %s\n\n", transportBar(elapsedSec_, song_.durationSec).c_str(),
           formatDuration(elapsedSec_).c_str(), formatDuration(song_.durationSec).c_str());
    console::info("Volume : " + std::to_string(app.settings().volume()));
    printf("\n");
    console::hint("p = play/pause, f/r = seek +/-15s, +/- = volume, x = stop, b = back");
}

void NowPlayingScreen::handleInput(App& app, const std::string& input) {
    if (input == "p") {
        paused_ = !paused_;
        app.setStatus(paused_ ? "Paused." : "Playing.");
        return;
    }
    if (input == "f" || input == "r") {
        const int delta = (input == "f") ? 15 : -15;
        elapsedSec_ += delta;
        if (elapsedSec_ < 0) elapsedSec_ = 0;
        if (elapsedSec_ > song_.durationSec) elapsedSec_ = song_.durationSec;
        app.setStatus("Seek to " + formatDuration(elapsedSec_));
        return;
    }
    if (input == "+" || input == "-") {
        const int delta = (input == "+") ? 5 : -5;
        app.settings().setVolume(app.settings().volume() + delta);
        app.setStatus("Volume " + std::to_string(app.settings().volume()));
        return;
    }
    if (input == "x") {
        app.setNowPlaying(nullptr);
        app.setStatus("Playback stopped.");
        app.pop();  // deferred by App, so it is safe to close ourselves here
        return;
    }
    app.setStatus("Unknown control: " + input);
}

} // namespace car
