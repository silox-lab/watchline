#include <sqlite3.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "../../include/storage/schema.h"

// get interface's rows, based on interface data provided.
IfDbStruct *db_get_interface(IfDbStruct if_struct, sqlite3 *db) {

    char sql[256];
    snprintf(sql, sizeof(sql), "SELECT * FROM interfaces WHERE name = '%s';", if_struct.name);

    sqlite3_stmt *stmt;
    int prepare_stat = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);

    if (prepare_stat != SQLITE_OK) {
        fprintf(stderr, "%s\n", sqlite3_errmsg(db));
    }

    int eval_stat = sqlite3_step(stmt);

    IfDbStruct *if_result = malloc(64); // result of query for return, 64 bit is for int field "id"
    if_result->name = malloc(101); // free it please 

    if (eval_stat == SQLITE_ROW) {
        const unsigned char *if_name_q = sqlite3_column_text(stmt, 1); // interface row name field

        int if_id_q = sqlite3_column_int(stmt, 0); // interface row id field
        strcpy(if_result->name, (char *)if_name_q); // copy to result interface
        if_result->id = if_id_q;

        return if_result;
    } else if (eval_stat == SQLITE_DONE) { // no row found
        if_result->name = NULL; // we use name field to indicate that no row has been found.
        return if_result;
    }

    fprintf(stderr, "%s\n", sqlite3_errmsg(db));
    return NULL; // null means there is an error
}

void db_make_interface(IfDbStruct if_struct, sqlite3 *db) {

    char *name = if_struct.name; // if means interface
    sqlite3_stmt *stmt; 

    if (strlen(name) > 101) perror("error: name is longer than 100 character.");

    char sql[256];
    snprintf(sql, sizeof(sql), "INSERT INTO interfaces VALUES (NULL, '%s')", name);

    int prepare_stat = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (prepare_stat != SQLITE_OK) {
        fprintf(stderr, "%s\n", sqlite3_errmsg(db));
    }
    sqlite3_step(stmt);
    int finalize_stat = sqlite3_finalize(stmt);
    if (finalize_stat != SQLITE_OK) {
        fprintf(stderr, "%s\n", sqlite3_errmsg(db));
    }
}

void db_make_table(char *table_sql, sqlite3 *db) {
    sqlite3_stmt *stmt;

    int prepare_stat = sqlite3_prepare_v2(db, table_sql, -1, &stmt, NULL);
    if (prepare_stat != SQLITE_OK) {
        fprintf(stderr, "%s\n", sqlite3_errmsg(db));
    }
    sqlite3_step(stmt);
    int finalize_stat = sqlite3_finalize(stmt);
    if (finalize_stat != SQLITE_OK) {
        fprintf(stderr, "%s\n", sqlite3_errmsg(db));
    }
}

void init_db() {
    sqlite3 *db;

    char *db_path = "watchline.db";
    int db_open = sqlite3_open(db_path, &db);

    if (db_open != SQLITE_OK) {
        fprintf(stderr, "%s\n", sqlite3_errmsg(db));
    }
    sqlite3_exec(db, "PRAGMA foreign_keys = ON;", NULL, NULL, NULL);

    db_make_table(TABLE_INTERFACES, db);
    db_make_table(TABLE_USAGE_RECORDS, db);
    
    sqlite3_close(db);
}