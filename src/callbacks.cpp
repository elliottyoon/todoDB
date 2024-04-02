#pragma once
#include <sqlite3.h>
#include <iostream>

#include <ctime>
#include <string>
#include <map>

static int callback(void *NotUsed, int argc, char **argv, char **azColName){
    int i;
    for(i=0; i<argc; i++){
        std::cout << azColName[i] << " = " << (argv[i] ? argv[i] : "NULL") << "\n";
    }
    std::cout << std::endl;
    return 0;
}

struct {
    std::string class_id;
    std::string class_name;
    std::time_t date;
    std::string description;
} exam_t;

static int list_exams(void *NotUsed, int argc, char **argv, char **azColName) {
    for (int i = 0; i < argc; i++) {
        std::cout << "(" << azColName[i] << ", " << (argv[i] ? argv[i] : "NULL") << ")" << "\n";
    }
    std::cout << std::endl;
    return 0;
}