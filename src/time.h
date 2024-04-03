#pragma once

#include <map>
#include <ctime>
#include <fstream>
#include <string>
#include <stdexcept>
#include <sstream>

const std::string FORMAT = "YYYY-MM-DD HH:MM:SS";
const std::unordered_map<std::string, int> monthToMM {
    {"JANUARY", 1}, {"JAN", 1},
    {"FEBRUARY", 2}, {"FEB", 2},
    {"MARCH", 3}, {"MAR", 3},
    {"APRIL", 4}, {"APR", 4},
    {"MAY", 5},
    {"JUNE", 6}, {"JUN", 6},
    {"JULY", 7}, {"JUL", 7},
    {"AUGUST", 8}, {"AUG", 8},
    {"SEPTEMBER", 9}, {"SEP", 9},
    {"OCTOBER", 10}, {"OCT", 10},
    {"NOVEMBER", 11}, {"NOV", 11},
    {"DECEMBER", 12}, {"DEC", 12}
};

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
    Time (int year, int month, int day, int hour, bool is_exam = true) : 
        year_(year), month_(month), day_(day), hour_(hour) {};

    Time (int year, std::string month, int day, int hour, bool is_exam = true) : 
        year_(year), month_(formatMonth(month)), day_(day), hour_(hour) {};

    Time (int year, int month, std::string day, int hour, bool is_exam = true) : 
        year_(year), month_(month), day_(formatDay(day)), hour_(hour) {};

    Time (int year, std::string month, std::string day, int hour, bool is_exam = true) : 
        year_(year), month_(formatMonth(month)), day_(formatDay(day)), hour_(hour) {};

    int year() {
        return year_;
    } int month() { return month_; } int day() { return day_;
    }
    int hour() {
        return hour_;
    }

    std::string formatDatetime() {
        std::ostringstream ss("");
        ss << year_ << "-"
            << (month_ < 10 ? "0" : "") << month_ << "-"
            << (day_ < 10 ? "0" : "") << day_ << " "
            << (hour_ < 10 ? "0" : "") << hour_ << ":"
            << (is_exam_ ? "00:00" : "59:59");
        return ss.str();
    }

    static std::string hoursToString(int hours) {
        if (hours == 0 || hours == 24) return "Midnight";
        if (hours == 12) return "Noon";
        if (hours < 12) return std::to_string(hours) + " AM";
        return std::to_string(hours - 12) + " PM"; 
    }

    /**
     * @brief takes a string representation of a month (either MM or name) and 
     *        returns it in MM format.
     */
    static int formatMonth(std::string month) {
        if (month.size() == 2)
        {
            int res = stoi(month);
            if (res == 0 || res > 12) {
                throw std::invalid_argument(month + " is not a valid month.");
            }
            return stoi(month);
        }
        for (auto &c : month) { c = toupper(c); }
        const auto &it = monthToMM.find(month);
        if (it == monthToMM.end()) {
            throw std::invalid_argument(month + " is not a valid month.");
        }
        return (*it).second;
    }
    static int formatDay(std::string day) {
        if (day.empty() || day.size() > 2) { 
            throw std::invalid_argument(day + " is not a valid day.");
        }
        int res = stoi(day);
        if (res > 31) {
            throw std::invalid_argument(day + " is not a valid day.");
        }
        return res;
    }

private:
    int year_;
    int month_;
    int day_;
    int hour_;
    bool is_exam_ = true;
};