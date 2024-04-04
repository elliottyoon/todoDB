#pragma once 

#include <iostream>
#include <sstream>
#include <stdexcept>
#include "time.h"

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

    /**
     * @brief Creates a SQL insert query from given attributes
     */
    std::string generateQuery() {
        if (course_id.empty() || course_name.empty() || date == nullptr || description.empty()){ 
            throw std::invalid_argument("Item missing attributes imperative to insertion."); 
        }
        std::string itemz;
        switch (type) {
            case ItemType::EXAM:
                itemz = "exams";
                break;
            case ItemType::ASSIGNMENT:
                itemz = "assignments";
                break;
            default:
                throw std::invalid_argument("Item type should be `exam` or `assignment`.");
        }
        return "INSERT INTO " + itemz + " VALUES(\'" 
                + course_id + "\', \'"
                + course_name + "\', \'"
                + date->formatDatetime() + "\', \'"
                + description 
            + "\');";
    }
} item_t;

static int callback(void *NotUsed, int argc, char **argv, char **azColName);

void completeItem(item_t &item);

} // namespace commands