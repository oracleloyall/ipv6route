#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <net/if.h>
#include <ifaddrs.h>
#include <netinet/in.h>
int GetIP_v4_and_v6_linux(int family, char *address, int size)
{
struct ifaddrs *ifap0, *ifap;
char buf[NI_MAXHOST];
char *interface = "eth0";
struct sockaddr_in *addr4;
struct sockaddr_in6 *addr6;
int ret;

if( NULL == address ) {
return -1;
}
if(getifaddrs(&ifap0)) {
return -1;
}
for( ifap = ifap0; ifap != NULL; ifap=ifap->ifa_next){
if(strcmp(interface, ifap->ifa_name) != 0) continue;
if(ifap->ifa_addr==NULL) continue;
if ((ifap->ifa_flags & IFF_UP) == 0) continue;
if(family != ifap->ifa_addr->sa_family) continue;

if(AF_INET == ifap->ifa_addr->sa_family) {
addr4 = (struct sockaddr_in *)ifap->ifa_addr;
if ( NULL != inet_ntop(ifap->ifa_addr->sa_family, 
(void *)&(addr4->sin_addr), buf, NI_MAXHOST) ){
if(size <= strlen(buf) ) break; 
strcpy(address, buf);
freeifaddrs(ifap0);
return 0;
}
else break;
}
else if(AF_INET6 == ifap->ifa_addr->sa_family) {
addr6 = (struct sockaddr_in6 *)ifap->ifa_addr;
if(IN6_IS_ADDR_MULTICAST(&addr6->sin6_addr)){
continue;
}
if(IN6_IS_ADDR_LINKLOCAL(&addr6->sin6_addr)){
continue;
}
if(IN6_IS_ADDR_LOOPBACK(&addr6->sin6_addr)){
continue;
}
if(IN6_IS_ADDR_UNSPECIFIED(&addr6->sin6_addr)){
continue;
}
if(IN6_IS_ADDR_SITELOCAL(&addr6->sin6_addr)){
continue;
}
if ( NULL != inet_ntop(ifap->ifa_addr->sa_family, 
(void *)&(addr6->sin6_addr), buf, NI_MAXHOST) ){
if(size <= strlen(buf) ) break; 
strcpy(address, buf);
freeifaddrs(ifap0);
return 0;
}
else break;
}
}
