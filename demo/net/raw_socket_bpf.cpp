#include <stdlib.h>
#include <stdio.h>
#include <sys/socket.h>
#include <net/if_arp.h>
#include <net/if.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <net/ethernet.h>
#include <netpacket/packet.h>

#include <linux/filter.h>

unsigned char buffer[102];
int main(int argc, char *argv[])
{
    int fd, n, i;
    struct sock_fprog filter;

    struct sock_filter code[] = {
        { 0x28, 0, 0, 0x0000000c },
        { 0x15, 0, 3, 0x00000806 },
        { 0x20, 0, 0, 0x00000012 },
        { 0x15, 0, 1, 0x06040002 },
        { 0x6, 0, 0, 0x00040000 },
        { 0x6, 0, 0, 0x00000000 }, 
    };
   
    filter.len = sizeof(code)/sizeof(struct sock_filter); 
    filter.filter = code;
    
    fd = socket(PF_PACKET, SOCK_RAW, htons(ETH_P_ALL));
    if (fd < 0 ) {
        perror("socket fail\n");
        exit(1);
    }
    //设置 sk_filter
    if (setsockopt(fd, SOL_SOCKET, SO_ATTACH_FILTER, &filter, sizeof(filter)) < 0) {
        perror("setsockopt fail\n"); 
        exit(1);   
    }

    /*block*/
    n = recvfrom(fd, buffer, sizeof(buffer), 0, NULL, NULL);
    if (n < 0) {
        perror("recvfrom none\n");
        exit(1);
    }

    for (i = 0; i < n ;i++) {
        printf("%02x ", buffer[i]);
    }
    
    return 0;
}