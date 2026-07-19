#include <net/if.h>
#include <stdio.h>
#include <string.h>
#include <sys/ioctl.h>
#include <unistd.h>

int main() {
  struct if_nameindex *if_ni, *i;

  if_ni = if_nameindex();
  if (if_ni == NULL) {
    perror("if_nameindex");
    return 1;
  }
  int sock = socket(AF_INET, SOCK_DGRAM, 0);
  if (sock < 0)
    goto cleanup;
  struct ifreq ifr;

  for (i = if_ni; i->if_index != 0; i++) {
    if (strcmp(i->if_name, "lo") == 0) continue;
      printf("interface : %s\n", i->if_name);
    memset(&ifr, 0, sizeof ifr);
    strncpy(ifr.ifr_name, i->if_name, sizeof ifr.ifr_name);
    ioctl(sock, SIOCGIFFLAGS, &ifr);
    _Bool up = ifr.ifr_flags & IFF_UP;
    _Bool running = ifr.ifr_flags & IFF_RUNNING;
    if (!up) {
      fprintf(stderr, "Interface is Down, Try: ip link set {interface name} up\nls /sys/class/net: to see available interfaces\n");
      continue;
    }
    if (!running) {
      fprintf(stderr, "not connected to an AP or driver issue\n");
      continue;
    }
    printf("interface is up and running\n");
  }
cleanup:
  if (sock >= 0)
    close(sock);
  if_freenameindex(if_ni);
  return 0;
}
