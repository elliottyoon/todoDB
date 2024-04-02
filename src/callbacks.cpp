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

enum Item { ASSIGNMENT, EXAM };

typedef struct item_t {
    std::string course_id;
    std::string course_name;
    std::shared_ptr<Time> date;
    std::string description;
    Item item;
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

}; // namespace commands