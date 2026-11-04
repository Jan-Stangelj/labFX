#include "stopwatch.hpp"

stopwatch::stopwatch() {
    m_start = std::chrono::high_resolution_clock::now();
}

void stopwatch::reset() {
    m_start = std::chrono::high_resolution_clock::now();
}

double stopwatch::get() const {
    auto now = std::chrono::high_resolution_clock::now();
    return std::chrono::duration<double>(now - m_start).count();
}