#include "callbacks.cpp"
#include "commands.cpp"
#include <sstream>
#include <string>

int main(int argc, char **argv) {

    if ( argc!=1 ){
        fprintf(stderr, "Usage: %s", argv[0]);
        return(1);
    }

    /** Initialize databse object */
    std::string filename = "db_items.db";
    commands::SQLiteWrapper sql{};
    sql.init(filename);

    /** Console shit */
    std::string query;
    std::istringstream iss("");
    while ((std::cout << ">>> ") && std::getline(std::cin, query)) {
        /** Parse command arguments, splitting on spaces. */
        std::istringstream(query).swap(iss);
        std::vector<std::string> command_args{};
        std::string arg;
        while(std::getline(iss, arg, ' ')) {
            command_args.emplace_back(std::move(arg));
        }

        /** Execute commands */
        commands::Executor exec{};
        if (command_args[0] == "quit") break;
        if (command_args[0] == "help")  
        {
            commands::Helper h{};
            h.accept(exec);
        }
        else if (command_args[0] == "new") 
        {
            commands::Creator c(sql.db(), std::move(command_args));
            c.accept(exec);
        }
        else if (command_args[0] == "list") 
        {
            commands::Lister l{};
            l.accept(exec);
        }
        else if (command_args[0] == "delete") 
        {
            commands::Deleter d{};
            d.accept(exec);
        }
        else {
            commands::syntaxError();
        }



        /** Insert */
        // else if (command_args[0] == "new") {
        //     if (command_args[1] == "exam") {                    // new exam
        //         commands::createExam(rc, db, zErrMsg);
        //         continue;
        //     }
        //     else if (command_args[1] == "assignment") {
        //         std::cout << "new assignment command not implemented yet. sorry!" << std::endl;
        //         continue;
        //     }
        // }

        // /** Delete */

        // /** Get */
        // else if (command_args[0] == "list") {
        //     std::cout << "not implemented. sorry!" << std::endl;
        // }
        // /** TODO: delete this. blah */
        // else if (query == "exams") commands::exams(rc, db, zErrMsg);

        /** Invalid command */
    }
    return 0;
};