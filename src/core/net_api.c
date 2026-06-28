#include <net/if.h>
#include <stdlib.h>
#include <ifaddrs.h>
#include <string.h>

char **get_interfaces_name() {
   
    struct ifaddrs *net_interface, *head_ifaddrs;
    
    getifaddrs(&net_interface);
    head_ifaddrs = net_interface;

    int capacity = 10;
    int length = 0;
    char **interface_arr = malloc(capacity * sizeof(char *));
    
     while(net_interface != NULL) {
        if (!(net_interface->ifa_flags & IFF_LOOPBACK)) {
             char *name = strdup(net_interface->ifa_name);       
             if (length >= capacity) {
                interface_arr = realloc(interface_arr, capacity+1 * sizeof(char *));
                capacity++;
             }
        interface_arr[length] = name;
        length++;
       }
       net_interface = net_interface->ifa_next;       
     };

    freeifaddrs(head_ifaddrs);
    return interface_arr;
}
