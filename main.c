#include "./include/core/net_api.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {

  char ** interfaces = get_interfaces_name();

  printf("%s\n", interfaces[0]);
  
  free(interfaces);
  return 0;
} 
