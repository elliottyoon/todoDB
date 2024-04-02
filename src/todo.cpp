#include "callbacks.cpp"

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
    // maybe wrap this in a function or something vvvv
    rc = sqlite3_exec(db, "SELECT * FROM exams;", list_exams, 0, &zErrMsg);
    if( rc!=SQLITE_OK ){
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }    
    // ^^^^^^^
    rc = sqlite3_exec(db, "SELECT * FROM assignments;", list_exams, 0, &zErrMsg);
    if( rc!=SQLITE_OK ){
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }

    sqlite3_close(db);
    return 0;
};