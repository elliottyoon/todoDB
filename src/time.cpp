#pragma once

#include <ctime>
#include <fstream>
#include <string>
#include <stdexcept>
#include <sstream>

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
        Time (int year, int month, int day, int hour) : year_(year), month_(month), day_(day), hour_(hour) {};

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

        std::string formatDatetime() {
            std::ostringstream ss("");
            ss << year_ << "-"
               << (month_ < 10 ? "0" : "") << month_ << "-"
               << (day_ < 10 ? "0" : "") << day_ << " "
               << (hour_ < 10 ? "0" : "") << hour_ << ":00:00"; 
            return ss.str();
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