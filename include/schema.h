#ifndef SCHEMA
#define SCHEMA

#define TABLE_INTERFACES "CREATE TABLE IF NOT EXISTS interfaces (" \
                         "id INTEGER PRIMARY KEY AUTOINCREMENT," \
                         "name VARCHAR(100) NOT NULL UNIQUE" \
                         ");" \

#define TABLE_USAGE_RECORDS "CREATE TABLE IF NOT EXISTS usage_records (" \
                      "id INTEGER PRIMARY KEY AUTOINCREMENT," \
                      "day INTEGER NOT NULL CHECK (day BETWEEN 1 AND 31)," \
                      "month INTEGER NOT NULL CHECK (month BETWEEN 1 AND 12)," \
                      "year INTEGER NOT NULL," \
                      "interface_id INTEGER," \
                      "FOREIGN KEY (interface_id) " \
                      "REFERENCES interfaces(id)" \
                      ");"

typedef struct {
    char *name;
    int id;
} IfDbStruct;

#endif