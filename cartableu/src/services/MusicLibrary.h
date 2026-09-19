#pragma once
#include <string>
#include <vector>

namespace car {

struct Song {
    std::string title;
    std::string artist;
    int durationSec = 0;
};

// Static, in-memory catalogue standing in for the real media scanner.
class MusicLibrary {
public:
    MusicLibrary();

    const std::vector<Song>& songs() const { return songs_; }
    const Song& at(size_t index) const { return songs_.at(index); }
    size_t size() const { return songs_.size(); }

private:
    std::vector<Song> songs_;
};

std::string formatDuration(int seconds);

} // namespace car
