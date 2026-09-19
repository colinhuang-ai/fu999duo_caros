#include "Settings.h"

namespace car {

void Settings::setVolume(int v) {
    if (v < 0) v = 0;
    if (v > 100) v = 100;
    volume_ = v;
}

void Settings::cycleLanguage() {
    if (language_ == "Tieng Viet") {
        language_ = "English";
    } else if (language_ == "English") {
        language_ = "Nihongo";
    } else {
        language_ = "Tieng Viet";
    }
}

} // namespace car
