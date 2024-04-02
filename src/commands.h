#pragma once

#include <memory>
#include <stdexcept>
#include <vector>
#include <string>
#include <sqlite3.h>

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
         * @brief Execute a query on a database and call a callback function on the result.
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

class Command : Visitable {
    public:
        enum CommandType { HELP, CREATE, LIST, DELETE };

        Command(CommandType type) : type_(type) {};
        CommandType type() { return type_; }
    private:
        CommandType type_;
};

class Helper : public Command {
    public:
        Helper(std::vector<std::string> &&args) 
            : Command(CommandType::HELP), args_(std::move(args)) {};
        void accept(Visitor &v) override;
        std::vector<std::string> args() { return args_; }
        /**
         * @brief print documentation for the command corresponding to this command
         */
        static std::string toString();
    private:
        std::vector<std::string> args_;
};
class Creator : public Command {
    public:
        Creator(sqlite3 *db, std::vector<std::string> &&args) 
            : Command(CommandType::CREATE), args_(std::move(args)), db_(db) {};
        void accept(Visitor &v) override;
        std::vector<std::string> args() { return args_; };
        sqlite3 *db() { return db_; }
        /**
         * @brief print documentation for the command corresponding to this command
         */
        static std::string toString();
    private:
        std::vector<std::string> args_;
        sqlite3 *db_;
};
class Lister : public Command {
    public:
        Lister() 
            : Command(CommandType::LIST) {};
        void accept(Visitor &v) override;
        /**
         * @brief print documentation for the command corresponding to this command
         */
        static std::string toString();
    private:

};
class Deleter : public Command {
    public:
        Deleter() 
            : Command(CommandType::DELETE) {};
        void accept(Visitor &v) override;
        /**
         * @brief print documentation for the command corresponding to this command
         */
        static std::string toString();
};

class Executor : public Visitor {
    public:
        void visit(Helper *) override;
        void visit(Creator *) override;
        void visit(Lister *) override;
        void visit(Deleter *) override;
};

} // namespace commands