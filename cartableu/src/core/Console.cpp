#include "Console.h"

#include <chrono>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <thread>

namespace car {
namespace console {
namespace {

const int kWidth = 58;

std::string repeat(char c, int n) { return std::string(static_cast<size_t>(n), c); }

std::string trim(const std::string& s) {
    const char* ws = " \t\r\n";
    const size_t b = s.find_first_not_of(ws);
    if (b == std::string::npos) return "";
    const size_t e = s.find_last_not_of(ws);
    return s.substr(b, e - b + 1);
}

} // namespace

void clear() {
    // Cheap portable reset: ANSI clear works on Windows Terminal and modern
    // conhost, and falls back to just scrolling elsewhere.
    std::cout << "\033[2J\033[H";
}

void rule() { std::cout << repeat('-', kWidth) << "\n"; }

void header(const std::string& title, const std::string& subtitle) {
    clear();
    std::cout << repeat('=', kWidth) << "\n";
    std::cout << "  " << title << "\n";
    if (!subtitle.empty()) std::cout << "  " << subtitle << "\n";
    std::cout << repeat('=', kWidth) << "\n\n";
}

void menu(const std::vector<std::string>& items) {
    for (size_t i = 0; i < items.size(); ++i) {
        std::printf("  [%zu] %s\n", i + 1, items[i].c_str());
    }
    std::cout << "\n";
}

void hint(const std::string& text) { std::cout << "  (" << text << ")\n\n"; }
void info(const std::string& text) { std::cout << "  " << text << "\n"; }
void error(const std::string& text) { std::cout << "  !! " << text << "\n"; }

bool readLine(const std::string& prompt, std::string& out) {
    std::cout << prompt;
    std::cout.flush();
    std::string line;
    if (!std::getline(std::cin, line)) return false;
    out = trim(line);
    return true;
}

void progress(const std::string& label, int steps, int stepMillis) {
    std::cout << "  " << label << "\n  [";
    std::cout.flush();
    for (int i = 0; i < steps; ++i) {
        std::this_thread::sleep_for(std::chrono::milliseconds(stepMillis));
        std::cout << '#';
        std::cout.flush();
    }
    std::cout << "] done\n";
}

bool parseIndex(const std::string& input, size_t count, size_t& outZeroBased) {
    if (input.empty()) return false;
    for (char c : input) {
        if (c < '0' || c > '9') return false;
    }
    const unsigned long long value = std::strtoull(input.c_str(), nullptr, 10);
    if (value == 0 || value > count) return false;
    outZeroBased = static_cast<size_t>(value - 1);
    return true;
}

void pause() {
    std::cout << "\n  Press Enter to continue...";
    std::cout.flush();
    std::string ignored;
    std::getline(std::cin, ignored);
}

} // namespace console
} // namespace car
