#include <net/if.h>
#include <stdio.h>
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

    while (net_interface != NULL) {
      if (!(net_interface->ifa_flags & IFF_LOOPBACK)) {
        if (length >= capacity) {
          interface_arr = realloc(interface_arr, (capacity *= 2) * sizeof(char *));
          capacity++;
        }
        int is_duplicate = 0;
        for (int i = 0; i < length; i++) {
         if (strcmp(interface_arr[i], net_interface->ifa_name) == 0) {
            is_duplicate = 1;
            break;
         };
        }
        if (is_duplicate == 1) {
         net_interface = net_interface->ifa_next;
         continue;
        };
        char *name = strdup(net_interface->ifa_name);
        interface_arr[length] = name;
        length++;
      }
      net_interface = net_interface->ifa_next;
    };

    freeifaddrs(head_ifaddrs);

    if (length >= capacity) {
      interface_arr = realloc(interface_arr, (capacity *= 2) * sizeof(char *));
      capacity++;
    }

    interface_arr[length] = NULL;
    length++;
    return interface_arr;
}

char *get_if_rxbytes(char *if_name) {

  char *rxbyte_path = malloc(128);
  strcpy(rxbyte_path, "/sys/class/net/");
  strcat(rxbyte_path, if_name);
  strcat(rxbyte_path, "/statistics/rx_bytes");

  FILE *rx_file;
  rx_file = fopen(rxbyte_path, "r");
  char *rxbytes = malloc(4096);

  fgets(rxbytes, 4096, rx_file);

  fclose(rx_file);
  free(rxbyte_path);

  return rxbytes;
}