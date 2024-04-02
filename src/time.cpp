#pragma once

#include <ctime>
#include <string>
#include <stdexcept>

const std::string FORMAT = "YYYY-MM-DD HH:MM:SS";

class Time {
    public:
        Time(std::string datetime) {
            if (datetime.size() != FORMAT.size()) {
                throw std::invalid_argument( "Input not DATETIME formatted string." );
            }
            year_ = stoi(datetime.substr(0, 4));
            month_ = stoi(datetime.substr(5, 7));
            day_ = stoi(datetime.substr(8, 10));
            hour_ = stoi(datetime.substr(11, 13));
        }

        int year() {
            return year_;
        }
        int month() {
            return month_;
        }
        int day() {
            return day_;
        }
        int hour() {
            return hour_;
        }

        static std::string hoursToString(int hours) {
            if (hours == 0 || hours == 24) return "Midnight";
            if (hours == 12) return "Noon";
            if (hours < 12) return std::to_string(hours) + " AM";
            return std::to_string(hours - 12) + " PM"; 
        }

    private:
        int year_;
        int month_;
        int day_;
        int hour_;
};