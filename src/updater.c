#include <sqlite3.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include "../include/net_api.h"
#include "../include/db.h"
#include "../include/schema.h"

/* thread 2: updater

updater whole purpose is to run a series of instruction,
parallel to main thread, every 2 seconds for:

get new network interfaces and insert them into database
(usecases are far beyond, but im listing what it does right now)

*/
void *updater(void *args) {

    sqlite3 *db;
    
    char *db_path = "watchline.db";
    int db_open = sqlite3_open(db_path, &db);

    if (db_open != SQLITE_OK) {
        fprintf(stderr, "%s\n", sqlite3_errmsg(db));
    }
    char **interfaces = get_interfaces_name(); // every system network interfaces
    while (true) {
        sleep(2);
        for (int i = 0; interfaces[i] != NULL; i++) { 
            char *if_name = interfaces[i];

            IfDbStruct new_if = {.name = if_name}; // new interface that we want to add (if not exists)
            IfDbStruct *check_if = db_get_interface(new_if, db); // check if interface already exists

            if (check_if->name == NULL) { // it means that an interface with same name doesnt exist and this is new interface
                db_make_interface(new_if, db);
                free(check_if->name); // name is heap allocated
            }

            free(if_name);
            free(interfaces);
            free(check_if);

            interfaces = get_interfaces_name(); // update the interfaces name for next iteration
        }
    }

    args = NULL;
    return args;
}