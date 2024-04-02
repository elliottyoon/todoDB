Note: To compile on MacOS use `g++ src/todo.cpp -lsqlite3` 

---

### Schema:
1. exams(**class_id* VARCHAR(255), class_name VARCHAR(255), date DATETIME, description VARCHAR(255))
2. assignments(*class_id* VARCHAR(255), class_name VARCHAR(255), date DATETIME, description VARCHAR(255))