#pragma once

#include "time.cpp"

#include <sqlite3.h>
#include <iostream>

#include <map>

namespace commands {

static int callback(void *NotUsed, int argc, char **argv, char **azColName){
    int i;
    for(i=0; i<argc; i++){
        std::cout << azColName[i] << " = " << (argv[i] ? argv[i] : "NULL") << "\n";
    }
    std::cout << std::endl;
    return 0;
}

enum ItemType { ASSIGNMENT, EXAM };

typedef struct item_t {
    std::string course_id;
    std::string course_name;
    std::shared_ptr<Time> date;
    std::string description;
    ItemType type;
} item_t;

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
        switch(item.)
    }
    if (item.description.empty()) 
    {

    }
}

}; // namespace commands