#pragma once
#include <string>

namespace car {

class App;

// One full-screen page of the head unit. The app owns a stack of these.
class Screen {
public:
    virtual ~Screen() = default;

    virtual std::string title() const = 0;

    // Draws the page. Called once before every input read.
    virtual void render(App& app) = 0;

    // Handles one already-trimmed input line. Global commands (b/h/q) are
    // consumed by App before this is called.
    virtual void handleInput(App& app, const std::string& input) = 0;
};

} // namespace car
