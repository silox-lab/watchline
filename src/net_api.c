#include <net/if.h>
#include <stdio.h>
#include <stdlib.h>
#include <ifaddrs.h>
#include <string.h>

char **get_interfaces_name() {
   
    struct ifaddrs *net_interface, *head_ifaddrs;
    
    getifaddrs(&net_interface); // it's a linked list contain interfaces
    head_ifaddrs = net_interface; // we keep the head (first memeber) to free the whole interface object

    int capacity = 10; // default capacity of the array that holds data interfaces name
    int length = 0; // current interfaces in array count
    char **interface_arr = malloc(capacity * sizeof(char *));

    while (net_interface != NULL) { // last item of interfaces in the linked list of net_interface returns NULL
      if (!(net_interface->ifa_flags & IFF_LOOPBACK)) { // don't count loopback as an interface
        if (length >= capacity) {
          interface_arr = realloc(interface_arr, (capacity *= 2) * sizeof(char *));
          capacity *= 2;
        }
        int is_duplicate = 0; // check if we have an interface with same name in our array
        for (int i = 0; i < length; i++) {
         if (strcmp(interface_arr[i], net_interface->ifa_name) == 0) {
            is_duplicate = 1;
            break;
         };
        }
        if (is_duplicate == 1) { 
         net_interface = net_interface->ifa_next; // set the interface we are checking to next one because we found duplicate
         continue; // jump to next iteration because current one is duplicate
        };
        char *name = strdup(net_interface->ifa_name);
        interface_arr[length] = name;
        length++;
      }
      net_interface = net_interface->ifa_next; /* set the interface we are checking to next one
      because we added current one to our array */
    };

    freeifaddrs(head_ifaddrs); // free the interfaces linked list

    if (length >= capacity) { // check interface array to see if it has enough space for array NULL terminator
      interface_arr = realloc(interface_arr, (capacity + 1) * sizeof(char *));
      capacity++;
    }

    interface_arr[length] = NULL; // array null terminator
    length++;
    return interface_arr;
}

/*
This function returns the number of bytes,
received since the interface came up
*/
char *get_if_rxbytes(char *if_name) {

  char *rxbyte_path = malloc(128);
  snprintf(rxbyte_path, 128, "/sys/class/net/%s/statistics/rx_bytes", if_name);

  FILE *rx_file;
  rx_file = fopen(rxbyte_path, "r");
  char *rxbytes = malloc(4096); // amount of bytes written

  fgets(rxbytes, 4096, rx_file);

  fclose(rx_file);
  free(rxbyte_path);

  return rxbytes;
}