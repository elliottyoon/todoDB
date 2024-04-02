#pragma once

#include <iostream>
#include <string>
#include <sqlite3.h>

#include "callbacks.cpp"

namespace commands {
    static inline void help() {
        std::cout << "List of Commands: WIP" << std::endl;
    }
    static inline void syntaxError() {
        std::cout << "Invalid command. Type `help` for a list of valid commands" << std::endl;
    }

    // change these later
    void exams(int &rc, sqlite3 *db, char *&zErrMsg) {
        rc = sqlite3_exec(db, "SELECT * FROM exams;", listExams, 0, &zErrMsg);
        if( rc!=SQLITE_OK ){
            fprintf(stderr, "SQL error: %s\n", zErrMsg);
            sqlite3_free(zErrMsg);
        }    
    }

    // change these later
} // namespace op