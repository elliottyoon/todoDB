#pragma once

#include <string>
#include <chrono>

#define CURR_YEAR 2024

#include "commands.h"
#include "callbacks.cpp"

namespace commands {
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

    /** Visitor visit overrides */
    void Executor::visit(Helper *h) {
        std::cout << (const char*[]){"HELP", "CREATE", "LIST", "DELETE"}[h->type()] << std::endl;

        if (h->args().size() == 1) // default 
        {
            std::cout << "almost there besties" << std::endl;
        }
        std::cout << "List of commands not implemented yet" << std::endl;
    }
    void Executor::visit(Creator *c) {
        std::cout << (const char*[]){"HELP", "CREATE", "LIST", "DELETE"}[c->type()] << std::endl;

        std::string query("SELECT * FROM exams;");
        SQLiteWrapper::executeQuery(c->db(), query, commands::callback);
    }
    void Executor::visit(Lister *l) {
        std::cout << (const char*[]){"HELP", "CREATE", "LIST", "DELETE"}[l->type()] << std::endl;

        std::cout << "Lister not implemented yet" << std::endl;
    }
    void Executor::visit(Deleter *d) {
        std::cout << (const char*[]){"HELP", "CREATE", "LIST", "DELETE"}[d->type()] << std::endl;


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