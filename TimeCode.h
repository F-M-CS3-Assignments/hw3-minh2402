#ifndef TIMECODE_H
#define TIMECODE_H

#include <iostream>
#include <string>

class TimeCode {
private:
    int hours;
    int minutes;
    int seconds;

public:
    // Constructors
    TimeCode();
    TimeCode(int h, int m, int s);

    // Getters
    int GetHours() const;
    int GetMinutes() const;
    int GetSeconds() const;
    
    // Converts TimeCode to total seconds
    int GetTimeCodeAsSeconds() const;

    // Operators
    TimeCode operator+(const TimeCode& other) const;
    TimeCode operator/(double divisor) const;

    // Utility
    std::string ToString() const;
};

#endif
