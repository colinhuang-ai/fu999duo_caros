#pragma once
#include <string>

namespace car {

// Head-unit preferences shared by every screen.
class Settings {
public:
    int volume() const { return volume_; }
    void setVolume(int v);

    bool darkTheme() const { return darkTheme_; }
    void toggleTheme() { darkTheme_ = !darkTheme_; }

    bool metricUnits() const { return metricUnits_; }
    void toggleUnits() { metricUnits_ = !metricUnits_; }

    const std::string& language() const { return language_; }
    void cycleLanguage();

    bool shuffle() const { return shuffle_; }
    void toggleShuffle() { shuffle_ = !shuffle_; }

    std::string themeName() const { return darkTheme_ ? "Dark" : "Light"; }
    std::string unitName() const { return metricUnits_ ? "km / km-h" : "mi / mph"; }

private:
    int volume_ = 40;
    bool darkTheme_ = true;
    bool metricUnits_ = true;
    bool shuffle_ = false;
    std::string language_ = "Tieng Viet";
};

} // namespace car
