#pragma once

#include "time.cpp"

#include <sqlite3.h>
#include <iostream>

#include <map>

static int callback(void *NotUsed, int argc, char **argv, char **azColName){
    int i;
    for(i=0; i<argc; i++){
        std::cout << azColName[i] << " = " << (argv[i] ? argv[i] : "NULL") << "\n";
    }
    std::cout << std::endl;
    return 0;
}

typedef struct exam_t {
    std::string class_id;
    std::string class_name;
    std::shared_ptr<Time> date;
    std::string description;
} exam_t;

static int listExams(void *NotUsed, int argc, char **argv, char **azColName) {

    exam_t exam = {argv[0], 
                argv[1], 
                std::make_shared<Time>(argv[2]),
                argv[3]};

    std::cout << exam.class_id << " "
              << exam.class_name << ": "
              << exam.description << " on "
              << exam.date->month() << "/" << exam.date->day() << " @ " 
              << Time::hoursToString(exam.date->hour()) << std::endl;
    return 0;
}