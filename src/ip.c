// #include <string.h>
#include <arpa/inet.h>
#include <ifaddrs.h>
#include <linux/if_link.h>
#include <net/if.h>
#include <netdb.h>
#include <stdio.h>

int main() {
  struct ifaddrs *ifaddr;
  getifaddrs(&ifaddr);
  char host[1025];
  //  char *target = "wlp2s0";
  int family;
  for (struct ifaddrs *ifa = ifaddr; ifa; ifa = ifa->ifa_next) {
    if (!ifa->ifa_addr) {
      fprintf(stderr, "no Address");
      continue;
    }
    family = ifa->ifa_addr->sa_family;
    //    if (strcmp(ifa->ifa_name, target) == 0) {
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
    // }
  }
  return 0;
}
