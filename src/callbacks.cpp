#pragma once

#include "commands.cpp"
#include "time.cpp"

#include <sqlite3.h>
#include <iostream>

#include <map>
#include <sstream>

namespace commands {

static int callback(void *NotUsed, int argc, char **argv, char **azColName){
    int i;
    for(i=0; i<argc; i++){
        std::cout << azColName[i] << " = " << (argv[i] ? argv[i] : "NULL") << "\n";
    }
    std::cout << std::endl;
    return 0;
}


static int listExams(void *NotUsed, int argc, char **argv, char **azColName) {
    item_t exam = {argv[0], 
                argv[1], 
                std::make_shared<Time>(argv[2]),
                argv[3], 
                EXAM};
    std::cout << exam.course_id << " "
              << exam.course_name << ": "
              << exam.description << " on "
              << exam.date->month() << "/" << exam.date->day() << " @ " 
              << Time::hoursToString(exam.date->hour()) << std::endl;
    return 0;
}

void completeItem(item_t &item) {
    std::string buffer;

    if (item.course_id.empty()) 
    {
        std::cout << "--- Course ID: ";
        getline(std::cin, buffer);
        item.course_id = buffer;
        for (auto &c : item.course_id) { c = toupper(c); }
    }
    if (item.course_name.empty()) 
    {
        /** TODO: create auxiliary table to map course_id to course_name */
        std::cout << "--- Course Name: ";
        getline(std::cin, buffer);
        item.course_name = buffer;
        for (auto &c : item.course_name) { c = toupper(c); }
    }
    if (item.date == nullptr) 
    {   
        std::cout << "--- Date (MM/DD or month day) ";
        getline(std::cin, buffer);
        std::istringstream iss(buffer);
        std::vector<std::string> mm_dd(2);
        for (int i = 0; i < 2; i++) {
            char delim = (buffer.find(('/') != std::string::npos) ? '/' : ' ');
            std::getline(iss, buffer, delim);
            mm_dd[i] = buffer;
        }
        item.date = std::make_shared<Time>(CURR_YEAR, mm_dd[0], mm_dd[1], 
                                           (item.type == ItemType::EXAM));
    }
    if (item.description.empty()) 
    {
        std::cout << "--- Description: ";
        getline(std::cin, buffer);
        item.description = buffer;
    }
    item.toString();
}

}; // namespace commands