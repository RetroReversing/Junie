#pragma once

#define SO_REUSEADDR 0
#define SO_BROADCAST 0
#define socket(domain, type, protocol) NULL
#define bind(sockfd, addr, addrlen) -1
#define setsockopt(sockfd, level, optname, optval, optlen) -1
#define sendto(sockfd, buf, len, flags, dest_addr, addrlen) 0
#define recvfrom(sockfd, buf, len, flags, src_addr, addrlen) 0

typedef void *pcap_handler;

typedef struct pcap_if_t
{
    char *name;
    char *description;
    struct pcap_if_t *next;
} pcap_if_t;

typedef struct
{
    int len;
} pcap_pkthdr;

int pcap_findalldevs(...) { return 0; }
int pcap_freealldevs(...) { return 0; }
void *pcap_open_live(...) { return NULL; }
void pcap_close(...) { }
int pcap_setnonblock(...) { return 0; }
int pcap_sendpacket(...) { return 0; }
int pcap_dispatch(...) { return 0; }
int pcap_breakloop(...) { return 0; }
