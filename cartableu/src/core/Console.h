#pragma once
#include <string>
#include <vector>

namespace car {

// Small helpers around stdout/stdin so the screens stay free of I/O details.
namespace console {

void clear();
void header(const std::string& title, const std::string& subtitle = "");
void rule();
void menu(const std::vector<std::string>& items);
void hint(const std::string& text);
void info(const std::string& text);
void error(const std::string& text);

// Blocking read of one trimmed line. Returns false when stdin is exhausted.
bool readLine(const std::string& prompt, std::string& out);

// Fake "work in progress" bar, used when loading map tiles / decoding audio.
void progress(const std::string& label, int steps, int stepMillis);

void pause();

// Parses a 1-based menu choice; false when it is not a number in [1, count].
bool parseIndex(const std::string& input, size_t count, size_t& outZeroBased);

} // namespace console
} // namespace car
