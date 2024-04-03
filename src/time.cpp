#pragma once

#include <map>
#include <ctime>
#include <fstream>
#include <string>
#include <stdexcept>
#include <sstream>

const std::string FORMAT = "YYYY-MM-DD HH:MM:SS";
const std::unordered_map<std::string, std::string> monthToMM {
    {"JANUARY", "01"}, {"JAN", "01"},
    {"FEBRUARY", "02"}, {"FEB", "02"},
    {"MARCH", "03"}, {"MAR", "03"},
    {"APRIL", "04"}, {"APR", "04"},
    {"MAY", "05"},
    {"JUNE", "06"}, {"JUN", "06"},
    {"JULY", "07"}, {"JUL", "07"},
    {"AUGUST", "08"}, {"AUG", "08"},
    {"SEPTEMBER", "09"}, {"SEP", "09"},
    {"OCTOBER", "10"}, {"OCT", "10"},
    {"NOVEMBER", "11"}, {"NOV", "11"},
    {"DECEMBER", "12"}, {"DEC", "12"}
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
    Time (int year, int month, int day, int hour) : 
        year_(year), month_(month), day_(day), hour_(hour) {};

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
            << (hour_ < 10 ? "0" : "") << hour_ << ":00:00"; 
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
    static std::string formatMonth(std::string month) {
        if (month.size() == 2)
        {
            if ((month[0] == '0' && month[1] == '0') || month[0] != '1') { 
                throw std::invalid_argument(month + " is not a valid month.");
            }
            return month;
        }
        for (auto &c : month) { c = toupper(c); }
        const auto &it = monthToMM.find(month);
        if (it == monthToMM.end()) {
            throw std::invalid_argument(month + " is not a valid month.");
        }
        return (*it).second;
    }

private:
    int year_;
    int month_;
    int day_;
    int hour_;
};