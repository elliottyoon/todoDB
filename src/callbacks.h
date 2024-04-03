#pragma once 

#include <iostream>
#include "time.cpp"

namespace commands {

enum ItemType { ASSIGNMENT, EXAM };

typedef struct item_t {
    std::string course_id;
    std::string course_name;
    std::shared_ptr<Time> date;
    std::string description;
    ItemType type;

    void toString() {
        std::cout << course_id << "(" << course_name << "): " 
                << (type == ItemType::ASSIGNMENT ? "Assignment due" : "Exam") << " @ "
                << date->formatDatetime() << ", "
                << description << std::endl;
    }
} item_t;

static int callback(void *NotUsed, int argc, char **argv, char **azColName);

void completeItem(item_t &item);

} // namespace commands