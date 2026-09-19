#pragma once
#include <string>
#include <vector>

namespace car {

struct MapRegion {
    std::string name;
    std::string code;
    int tileCount = 0;
};

// Loaded map: a tiny ASCII grid plus the vehicle position on it.
struct LoadedMap {
    std::string regionName;
    std::vector<std::string> grid;
    int carRow = 0;
    int carCol = 0;
};

class MapService {
public:
    MapService();

    const std::vector<MapRegion>& regions() const { return regions_; }
    const MapRegion& at(size_t index) const { return regions_.at(index); }
    size_t size() const { return regions_.size(); }

    // Simulates fetching tiles for a region; prints a progress bar.
    LoadedMap load(const MapRegion& region) const;

    // Moves the car one cell if the target cell is drivable.
    static bool move(LoadedMap& map, int dRow, int dCol);

    // Renders the window of the grid around the car; a smaller radius is a
    // closer zoom level.
    static std::string render(const LoadedMap& map, int rowRadius, int colRadius);

private:
    std::vector<MapRegion> regions_;
};

} // namespace car
