#include "MapService.h"

#include "../core/Console.h"

namespace car {
namespace {

const int kRows = 11;
const int kCols = 40;

char tileAt(int row, int col, unsigned seed) {
    const bool horizontalRoad = (row % 3) == 1;
    const bool verticalRoad = ((col + static_cast<int>(seed % 4)) % 6) == 1;
    if (horizontalRoad || verticalRoad) return '.';
    // A handful of deterministic points of interest sprinkled on the blocks.
    const unsigned h = (static_cast<unsigned>(row) * 7919u + static_cast<unsigned>(col) * 104729u + seed);
    if (h % 37 == 0) return 'P';  // parking
    if (h % 53 == 0) return 'F';  // fuel
    return '#';
}

unsigned seedOf(const std::string& code) {
    unsigned seed = 2166136261u;
    for (char c : code) {
        seed ^= static_cast<unsigned char>(c);
        seed *= 16777619u;
    }
    return seed;
}

bool drivable(char tile) { return tile == '.'; }

} // namespace

MapService::MapService()
    : regions_{
          {"Ha Noi - Inner City", "HAN", 128},
          {"Da Nang - Coastal", "DAD", 96},
          {"Ho Chi Minh City", "SGN", 164},
          {"Offline cache (last trip)", "CACHE", 24},
      } {}

LoadedMap MapService::load(const MapRegion& region) const {
    const unsigned seed = seedOf(region.code);

    console::info("Region : " + region.name);
    console::info("Tiles  : " + std::to_string(region.tileCount));
    console::progress("Downloading tiles...", 20, region.code == "CACHE" ? 5 : 40);
    console::progress("Building route graph...", 12, 25);

    LoadedMap map;
    map.regionName = region.name;
    map.grid.reserve(kRows);
    for (int r = 0; r < kRows; ++r) {
        std::string line;
        line.reserve(kCols);
        for (int c = 0; c < kCols; ++c) line.push_back(tileAt(r, c, seed));
        map.grid.push_back(line);
    }

    // Drop the car on the first drivable tile.
    for (int r = 0; r < kRows && map.carRow == 0 && map.carCol == 0; ++r) {
        for (int c = 0; c < kCols; ++c) {
            if (drivable(map.grid[r][c])) {
                map.carRow = r;
                map.carCol = c;
                break;
            }
        }
    }
    return map;
}

bool MapService::move(LoadedMap& map, int dRow, int dCol) {
    const int r = map.carRow + dRow;
    const int c = map.carCol + dCol;
    if (r < 0 || r >= static_cast<int>(map.grid.size())) return false;
    if (c < 0 || c >= static_cast<int>(map.grid[r].size())) return false;
    if (!drivable(map.grid[r][c])) return false;
    map.carRow = r;
    map.carCol = c;
    return true;
}

std::string MapService::render(const LoadedMap& map, int rowRadius, int colRadius) {
    const int rows = static_cast<int>(map.grid.size());
    const int cols = rows > 0 ? static_cast<int>(map.grid[0].size()) : 0;

    int top = map.carRow - rowRadius;
    int bottom = map.carRow + rowRadius;
    int left = map.carCol - colRadius;
    int right = map.carCol + colRadius;
    if (top < 0) top = 0;
    if (left < 0) left = 0;
    if (bottom > rows - 1) bottom = rows - 1;
    if (right > cols - 1) right = cols - 1;

    std::string out;
    for (int r = top; r <= bottom; ++r) {
        out += "  ";
        for (int c = left; c <= right; ++c) {
            out.push_back((r == map.carRow && c == map.carCol) ? 'A' : map.grid[r][c]);
        }
        out.push_back('\n');
    }
    return out;
}

} // namespace car
