// #include <string.h>
#include <arpa/inet.h>
#include <ifaddrs.h>
#include <linux/if_link.h>
#include <net/if.h>
#include <netdb.h>
#include <netpacket/packet.h>
#include <stdio.h>

int main() {
  struct ifaddrs *ifaddr;
  getifaddrs(&ifaddr);
  char host[1025];
  //  char *target = "wlp2s0";
  int family;
  for (struct ifaddrs *ifa = ifaddr; ifa; ifa = ifa->ifa_next) {
    if (!ifa->ifa_addr) {
      fprintf(stderr, "no Address for %s\n", ifa->ifa_name);
      continue;
    }
    family = ifa->ifa_addr->sa_family;
    //    if (strcmp(ifa->ifa_name, target) == 0) {
    if (family == AF_PACKET) {
      struct sockaddr_ll *sl = (struct sockaddr_ll *)ifa->ifa_addr;
      if (sl->sll_halen == 6) {
        snprintf(host, sizeof(host), "%02x:%02x:%02x:%02x:%02x:%02x",
                 sl->sll_addr[0], sl->sll_addr[1], sl->sll_addr[2],
                 sl->sll_addr[3], sl->sll_addr[4], sl->sll_addr[5]);
        printf("MAC Address of the interface %s :%s\n", ifa->ifa_name, host);
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
    // }
  }
  freeifaddrs(ifaddr);
  return 0;
}
