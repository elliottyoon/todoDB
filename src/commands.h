#pragma once

#include <memory>
#include <stdexcept>
#include <vector>
#include <string>
#include <sqlite3.h>

// debugging
#include <iostream>

namespace commands {

class SQLiteWrapper {
    public:
        SQLiteWrapper() = default;
        ~SQLiteWrapper() { sqlite3_close(db_); }

        SQLiteWrapper(const SQLiteWrapper &&sql) : db_(sql.db_) {};
        SQLiteWrapper(const SQLiteWrapper &) = delete;
        SQLiteWrapper& operator=(const SQLiteWrapper &) = delete;
        /**
         * @brief Initialize wrapper object with a given database file
         * 
         * @param filename the name of the database file
         */
        inline void init(std::string &filename) {
            int rc = sqlite3_open(&filename[0], &db_);
            if ( rc ) {
                fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db_));
                sqlite3_close(db_);
                throw std::invalid_argument("Can't open database %s\n");
            }
        }
        /**
         * @brief 
         * 
         * @param db database.
         * @param query SQL query to be executed on `db`
         * @param callback function that does stuff with the output of the `query` when executed
         */
        static void executeQuery(sqlite3 * const db, std::string &query, int (*callback)(void *, int, char **, char **));

        sqlite3 *db() { return db_; } 

    private:
        sqlite3 *db_;
};

class Visitor {
    public:
        virtual void visit(class Helper *) = 0;
        virtual void visit(class Creator *) = 0;
        virtual void visit(class Lister *) = 0;
        virtual void visit(class Deleter *) = 0;
};

class Visitable {
    public:
        virtual void accept(Visitor &v) = 0;
};

class Helper : public Visitable {
    public:
        Helper() {};
        void accept(Visitor &v) override;
};
class Creator : public Visitable {
    public:
        Creator(sqlite3 *db, std::vector<std::string> &&args) 
            : args_(std::move(args)), db_(db) {};
        void accept(Visitor &v) override;
        std::vector<std::string> args() { return args_; };
        sqlite3 *db() { return db_; }
    private:
        std::vector<std::string> args_;
        sqlite3 *db_;
};
class Lister : public Visitable {
    public:
        Lister() {};
        void accept(Visitor &v) override;
};
class Deleter : public Visitable {
    public:
        Deleter() {};
        void accept(Visitor &v) override;
};

class Executor : public Visitor {
    public:
        void visit(Helper *) override;
        void visit(Creator *) override;
        void visit(Lister *) override;
        void visit(Deleter *) override;
};

} // namespace commands