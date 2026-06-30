#ifndef DB
#define DB
#include <sqlite3.h>
#include "./schema.h"

void init_db();
void db_make_table(char *table_sql, sqlite3 *db);
void db_make_interface(IfDbStruct if_struct, sqlite3 *db);
IfDbStruct *db_get_interface(IfDbStruct if_struct, sqlite3 *db);

#endif