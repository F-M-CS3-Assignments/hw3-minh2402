#include "TimeCode.h"
#include <iomanip>
#include <sstream>

// Default constructor
TimeCode::TimeCode() : hours(0), minutes(0), seconds(0) {}

// Constructor with parameters
TimeCode::TimeCode(int h, int m, int s) : hours(h), minutes(m), seconds(s) {}

// Getters
int TimeCode::GetHours() const { return hours; }
int TimeCode::GetMinutes() const { return minutes; }
int TimeCode::GetSeconds() const { return seconds; }

// Converts TimeCode to total seconds
int TimeCode::GetTimeCodeAsSeconds() const {
    return (hours * 3600) + (minutes * 60) + seconds;
}

// Overloaded addition operator
TimeCode TimeCode::operator+(const TimeCode& other) const {
    int totalSeconds = GetTimeCodeAsSeconds() + other.GetTimeCodeAsSeconds();
    int h = totalSeconds / 3600;
    int m = (totalSeconds % 3600) / 60;
    int s = totalSeconds % 60;
    return TimeCode(h, m, s);
}

// Overloaded division operator
TimeCode TimeCode::operator/(double divisor) const {
    int totalSeconds = GetTimeCodeAsSeconds() / divisor;
    int h = totalSeconds / 3600;
    int m = (totalSeconds % 3600) / 60;
    int s = totalSeconds % 60;
    return TimeCode(h, m, s);
}

// Converts TimeCode to a string
std::string TimeCode::ToString() const {
    std::ostringstream oss;
    oss << hours << ":" << minutes << ":" << seconds;
    return oss.str();
}

