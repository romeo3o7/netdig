#include <string.h>
// #define _GNU_SOURCE /* To get defns of NI_MAXSERV and NI_MAXHOST */
// #include <arpa/inet.h>
#include <ifaddrs.h>
// #include <linux/if_link.h>
#include <net/if.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
// #include <sys/ioctl.h>
// #include <sys/socket.h>
// #include <unistd.h>
#include <arpa/inet.h>
int main(int argc, char *argv[]) {
  struct ifaddrs *ifaddr;
  int family ;
  _Bool found = 0;
  char host[1025];

  if (getifaddrs(&ifaddr) == -1) {
    perror("getifaddrs");
    exit(EXIT_FAILURE);
  }
  for (struct ifaddrs *ifa = ifaddr; ifa != NULL; ifa = ifa->ifa_next) {
    if (ifa->ifa_addr == NULL || strcmp(ifa->ifa_name, "lo") == 0) {
      continue;
    }
    family = ifa->ifa_addr->sa_family;
    if (family == AF_PACKET) {
      found = 1;
      printf("interface name :%s\n", ifa->ifa_name);

      _Bool hardwareUp = ifa->ifa_flags & IFF_RUNNING;
      _Bool softwareUp = ifa->ifa_flags & IFF_UP;

      if (!hardwareUp) {
        printf("interface down, driver down or hardware down\n");
        continue;
      }
      if (!softwareUp) {
        printf("interface down, not enabled\n");
        continue;
      }
    }

    if (family == AF_INET) {
      struct sockaddr_in *sa = (struct sockaddr_in *)ifa->ifa_addr;
      inet_ntop(AF_INET, &sa->sin_addr, host, sizeof(host));
      printf("IPV4 Address of the interface %s :%s\n", ifa->ifa_name, host);
    }
    if (family == AF_INET6) {
      struct sockaddr_in6 *sa6 = (struct sockaddr_in6 *)ifa->ifa_addr;
      inet_ntop(AF_INET6, &sa6->sin6_addr, host, sizeof(host));
      printf("IPV6 Address of the interface %s :%s\n", ifa->ifa_name, host);
    }
  }
  if (!found)
    printf("no interface found\n");
  freeifaddrs(ifaddr);
  exit(EXIT_SUCCESS);
}
