// AUTHOR: DUC MINH PHAM
// DATE: FEB 18, 2025

#include "TimeCode.h"
#include <stdexcept>
#include <iomanip>
#include <sstream>

// Constructor: Converts input to total seconds (t) with rollover handling
TimeCode::TimeCode(unsigned int hr, unsigned int min, long long unsigned int sec) {
    t = ComponentsToSeconds(hr, min, sec);
}

// Copy Constructor
TimeCode::TimeCode(const TimeCode& tc) {
    t = tc.t;
}

// Setters (without rollover, only setting specific components)
void TimeCode::SetHours(unsigned int hours) {
    unsigned int h, m;
    long long unsigned int s;
    GetComponents(h, m, s);
    t = ComponentsToSeconds(hours, m, s);
}

void TimeCode::SetMinutes(unsigned int minutes) {
    if (minutes >= 60) throw std::invalid_argument("Minutes must be < 60");
    unsigned int h, m;
    long long unsigned int s;
    GetComponents(h, m, s);
    t = ComponentsToSeconds(h, minutes, s);
}

void TimeCode::SetSeconds(long long unsigned int seconds) {
    unsigned int h, m;
    long long unsigned int s;
    GetComponents(h, m, s);
    t = ComponentsToSeconds(h, m, seconds);
}

// Reset time to 0:0:0
void TimeCode::reset() {
    t = 0;
}

// Getters
unsigned int TimeCode::GetHours() const {
    return t / 3600;
}

unsigned int TimeCode::GetMinutes() const {
    return (t % 3600) / 60;
}

unsigned int TimeCode::GetSeconds() const {
    return t % 60;
}

// Convert total seconds to hours, minutes, seconds
void TimeCode::GetComponents(unsigned int& hr, unsigned int& min, long long unsigned int& sec) const {
    hr = t / 3600;
    min = (t % 3600) / 60;
    sec = t % 60;
}

// Static method to convert components to total seconds
long long unsigned int TimeCode::ComponentsToSeconds(unsigned int hr, unsigned int min, long long unsigned int sec) {
    return (hr * 3600) + (min * 60) + sec;
}

// Return time as formatted string "hh:mm:ss"
std::string TimeCode::ToString() const {
    unsigned int h, m;
    long long unsigned int s;
    GetComponents(h, m, s);
    std::ostringstream oss;
    oss << h << ":" << m << ":" << s;
    return oss.str();
}

// Operators
TimeCode TimeCode::operator+(const TimeCode& other) const {
    return TimeCode(0, 0, t + other.t);
}

TimeCode TimeCode::operator-(const TimeCode& other) const {
    if (t < other.t) throw std::invalid_argument("Negative TimeCode not allowed");
    return TimeCode(0, 0, t - other.t);
}

TimeCode TimeCode::operator*(const TimeCode& other) const {
    return TimeCode(0, 0, t * other.t);
}

TimeCode TimeCode::operator/(const TimeCode& other) const {
    if (other.t == 0) throw std::invalid_argument("Cannot divide by zero");
    return TimeCode(0, 0, t / other.t);
}

// Comparison Operators
bool TimeCode::operator==(const TimeCode& other) const { return t == other.t; }
bool TimeCode::operator!=(const TimeCode& other) const { return t != other.t; }
bool TimeCode::operator<(const TimeCode& other) const { return t < other.t; }
bool TimeCode::operator>(const TimeCode& other) const { return t > other.t; }
bool TimeCode::operator<=(const TimeCode& other) const { return t <= other.t; }
bool TimeCode::operator>=(const TimeCode& other) const { return t >= other.t; }
