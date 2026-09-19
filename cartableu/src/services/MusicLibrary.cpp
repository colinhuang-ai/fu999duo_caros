#include "MusicLibrary.h"

#include <cstdio>

namespace car {

MusicLibrary::MusicLibrary()
    : songs_{
          {"Duong Toi Cho Ve", "Buc Tuong", 294},
          {"Highway Star", "Deep Purple", 367},
          {"Mat Troi Cua Em", "Phuong Ly", 218},
          {"Take Five", "Dave Brubeck", 324},
          {"Nocturne Op.9 No.2", "Chopin", 271},
          {"Radio Ga Ga", "Queen", 348},
      } {}

std::string formatDuration(int seconds) {
    char buf[16];
    std::snprintf(buf, sizeof(buf), "%d:%02d", seconds / 60, seconds % 60);
    return buf;
}

} // namespace car
