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
            commands::Helper h(std::move(command_args));
            h.accept(exec);
        }
        else if (command_args[0] == "new") 
        {
            // add support for bypassing menu vvv 
            // if (command_args.size() != 1)
            commands::Creator c{sql.db(), std::move(command_args)};
            c.accept(exec);
        }
        else if (command_args[0] == "list") 
        {
            commands::Lister l{sql.db(), std::move(command_args)};
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
    }
    return 0;
};