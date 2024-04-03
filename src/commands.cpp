#pragma once

#include <algorithm>
#include <cctype>
#include <string>
#include <chrono>
#include <iostream>
#include <unordered_map>

#define CURR_YEAR 2024

#include "commands.h"
#include "callbacks.h"

namespace commands {

    std::string Helper::toString() {
        return "`help [command0 command1 ...]=[help create list delete]`\n\
                - Print documentation for specified commands.\n\
                - Note the command list argument defaults to all commands.\n\
                1. *command_i* is a console command (i.e. one of `help`, `create`, `list`, `delete`).";
    }
    std::string Creator::toString() {
        return "TODO creator";
    }
    std::string Lister::toString() {
        return "TODO lister";
    }
    std::string Deleter::toString() {
        return "TODO deleter";
    }

    void SQLiteWrapper::executeQuery(sqlite3 * const db, std::string &query, int (*callback)(void *, int, char **, char **)) {
        char* zErrMsg = 0;
        int rc = sqlite3_exec(db, &query[0], callback, 0, &zErrMsg);
        if( rc!=SQLITE_OK ){
            fprintf(stderr, "SQL error: %s\n", zErrMsg);
            sqlite3_free(zErrMsg);
        }   
    }

    static inline void syntaxError() { std::cout << "Invalid command. Type `help` for a list of valid commands" << std::endl; }

    /** Visitable accept overrides */
    void Helper::accept(Visitor &v) { v.visit(this); }
    void Creator::accept(Visitor &v) { v.visit(this); }
    void Lister::accept(Visitor &v) { v.visit(this); }
    void Deleter::accept(Visitor &v) { v.visit(this); }

    std::unordered_map<std::string, Command::CommandType> command_name_to_type {
        {"help", Command::CommandType::HELP},
        {"new", Command::CommandType::CREATE},
        {"list", Command::CommandType::LIST},
        {"delete", Command::CommandType::DELETE}
    };
    /** Visitor visit overrides */
    void Executor::visit(Helper *h) {
        if (h->args().size() == 1) // default 
        {
            std::cout << Helper::toString() << '\n'
                      << Creator::toString() << '\n'
                      << Lister::toString() << '\n'
                      << Deleter::toString() << std::endl;
            return;
        }
        for (size_t i = 1; i < h->args().size(); i++) {
            /** Parse individual argument */
            std::string arg = h->args()[i];
            for (auto &c : arg) c = std::tolower(c);
            /** Print the correct documentation for the corresponding command */
            switch(command_name_to_type[arg]) {
                case Command::CommandType::HELP:
                    std::cout << Helper::toString() << std::endl;
                    break;
                case Command::CommandType::CREATE:
                    std::cout << Creator::toString() << std::endl;
                    break;
                case Command::CommandType::LIST:
                    std::cout << Lister::toString() << std::endl;
                    break;
                case Command::CommandType::DELETE:
                    std::cout << Deleter::toString() << std::endl;
                    break;
            }
        }

    }
    void Executor::visit(Creator *c) {
        /** TODO: support partial creation from CLI */
        /** TODO: argv[1] should be EXAM or ASSIGNMENT, set type of item using this */
        commands::item_t item;
        completeItem(item);
        
        // std::string query("SELECT * FROM exams;");
        // SQLiteWrapper::executeQuery(c->db(), query, commands::callback);
    }
    void Executor::visit(Lister *l) {
        std::cout << "Lister not implemented yet" << std::endl;
    }
    void Executor::visit(Deleter *d) {
        std::cout << "Deleter not implemented yet" << std::endl;
    }
    
    // // change these later
    // void exams(int &rc, sqlite3 *db, char *&zErrMsg) {
    //     rc = sqlite3_exec(db, "SELECT * FROM exams;", listExams, 0, &zErrMsg);
    //     if( rc!=SQLITE_OK ){
    //         fprintf(stderr, "SQL error: %s\n", zErrMsg);
    //         sqlite3_free(zErrMsg);
    //     }    
    // }

    // void createExam(int &rc, sqlite3 *db, char *&zErrMsg) {
    //     /** Get Exam information */
    //     std::string buffer;

    //     std::cout << "-- Course ID: ";
    //     getline(std::cin, buffer);
    //     std::string course_id = buffer;
    //     for (auto &c : course_id) c = toupper(c); 

    //     std::cout << "-- Course Name: ";
    //     getline(std::cin, buffer);
    //     std::string course_name = buffer;
    //     for (int i = 0; i < course_name.size(); i++) {
    //         course_name[i] = (i == 0 || course_name[i-1] == ' ') 
    //             ? toupper(course_name[i]) 
    //             : tolower(course_name[i]);
    //     }

    //     std::cout << "-- Month: ";
    //     getline(std::cin, buffer);
    //     int month = stoi(buffer);
    //     std::cout << "-- Day: ";
    //     getline(std::cin, buffer);
    //     int day = stoi(buffer);
    //     std::cout << "-- Hour: ";
    //     getline(std::cin, buffer);
    //     int hour = stoi(buffer);
    //     // std::cout << "-- Year: ";
    //     int year = CURR_YEAR;
    //     Time t{year, month, day, hour};

    //     std::cout << "-- Description: ";
    //     getline(std::cin, buffer);
    //     std::string description = buffer;
        
    //     /** Create Exam object with collected information */
    //     const std::string query = "INSERT INTO exams VALUES(\'" 
    //                             + std::move(course_id) + "\', \'"
    //                             + std::move(course_name) + "\', \'" 
    //                             + t.formatDatetime() + "\', \'"
    //                             + std::move(description)
    //                             + "\');";
    //     std::cout << query << std::endl;
    //     rc = sqlite3_exec(db, &query[0], callback, 0, &zErrMsg);
    //     if( rc!=SQLITE_OK ){
    //         fprintf(stderr, "SQL error: %s\n", zErrMsg);
    //         sqlite3_free(zErrMsg);
    //     }   
    // }

} // namespace op