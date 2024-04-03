Note: To compile on MacOS use `g++ src/main.cpp -lsqlite3 -std=c++17` 

---
DATETIME  YYYY-MM-DD HH:MM:SS

### Schema:
1. exams(**class_id* VARCHAR(255), class_name VARCHAR(255), date DATETIME, description VARCHAR(255))
2. assignments(*class_id* VARCHAR(255), class_name VARCHAR(255), date DATETIME, description VARCHAR(255))

---

### Commands
* `help [command0 command1 ...]=[help create list delete]` : Print documentation for specified commands. Note the command list argument defaults to all commands.
    1. *command_i* is a console command (i.e. one of `help`, `create`, `list`, `delete`).";
* `quit` : Exit the console.
* `new [item_type]` : Create an item.
    1. *item_type* is either a class or exam
* `delete [class]` : Delete an item from a given class.
    1. *class* is either a class name or class id (e.g. "Operating Systems" or "CS343")
* `list [class]=all [item_type] [time_duration]=both [group_by]=datetime` : For class *class*, list all items of item type *item_type* in a given *time_duration*, grouped by attribute *group_by*. 
    1. *class* is either a class name or class id (e.g. "Graph Theory" or "Math308"). 
    2. *item_type* can be `exam`, `assignment`, or `both`.
    3. *time_duration* can be `day`, `week`, `month`, or `all`.
    4. *group_by* can be `class` or `datetime`. 