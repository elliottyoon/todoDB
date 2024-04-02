#include "callbacks.cpp"
#include "commands.cpp"
#include <string>

int main(int argc, char **argv) {
    sqlite3 *db;
    char *zErrMsg = 0; 
    int rc;

    // if( argc!=3 ){
    //     fprintf(stderr, "Usage: %s DATABASE SQL-STATEMENT\n", argv[0]);
    //     return(1);
    // }
    if ( argc!=1 ){
        fprintf(stderr, "Usage: %s", argv[0]);
        return(1);
    }

    std::string filename = "db_items.db";
    rc = sqlite3_open(&filename[0], &db);
    if( rc ){
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return(1);
    }

    std::string query;
    while ((std::cout << ">>> ") && std::getline(std::cin, query)) {
        if (query == "quit" || query == "exit") break;
        if (query == "help") commands::help();
        else if (query == "exams") commands::exams(rc, db, zErrMsg);
        else if (query == "new exam") commands::createExam(rc, db, zErrMsg);
        else commands::syntaxError();
    }


    // maybe wrap this in a function or something vvvv
    sqlite3_close(db);
    return 0;
};