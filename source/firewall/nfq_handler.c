/**********************************************************************
   Copyright [2014] [Cisco Systems, Inc.]
 
   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at
 
       http://www.apache.org/licenses/LICENSE-2.0
 
   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
**********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <arpa/inet.h>
//#include <netinet/in.h>
//#include <netdb.h>
//#include <linux/ip.h>
#include <netinet/ether.h> 
#include <netinet/ip.h>
#include <netinet/ip6.h>
#include <linux/udp.h>
#include <linux/tcp.h>
#include <libnetfilter_queue/libnetfilter_queue.h>
#include <linux/netfilter.h>
#include <sys/ioctl.h>
#include <net/if.h>

#define _NFQ_DEBUG_LEVEL 0
#define PARCON_IP_PATH "/var/parcon/"

void send_tcp_pkt(char *interface, int family, char *srcMac, char *dstMac, char *srcIp, char *dstIp, unsigned short srcPort, unsigned short dstPort, unsigned long seqNum, unsigned long ackNum, char *url, unsigned char fin);

char srcMac[20];

struct __attribute__((__packed__)) dns_header
{
    __u16 id;
    __u16 flags;
    __u16 questions;
    __u16 answerRR;
    __u16 authRR;
    __u16 extraRR;
};

struct __attribute__((__packed__)) dns_answer
{
    __u16 offset;   //TO-DO only support fully compressed name format
    __u16 type;
    __u16 class;
    __u32 ttl;
    __u16 len;
};

typedef enum {
    BLOCK_BY_URL,
    BLOCK_BY_KEYWD
} block_type;

static char *get_dns_header(char *payload)
{
    //Use kernel iphdr/udphdr struct to parse the packet
    struct iphdr *ipHdr = (struct iphdr *)(payload);
    struct udphdr *udpHdr;
    if(ipHdr->version == 4){
        udpHdr = (struct udphdr *)(payload + ((struct iphdr*)payload)->ihl * 4);
    }else{
        struct ip6_hdr *ip6Hdr = (struct ip6Hdr *)(payload);
        udpHdr = (struct udphdr *)(payload + sizeof(struct ip6_hdr));
    }
    return (char *)udpHdr + sizeof(struct udphdr);
}

//Get pointer to the start of url in the packet assuming there is only one question
//Note: Neither DjbDNS, BIND, nor MSDNS support queries where QDCOUNT > 1
static int get_query_url(char *url, char* dnsData)
{
    char *ptr = url;
    unsigned char l;
    int i, len = 0;

    //Convert the url hex data to string
    //03www05cisco03com -> www.cisco.com
    while(*dnsData != 0) {
        l = *dnsData;
        len += l+1;

        ++dnsData;

        for(i = 0; i < l; ++i, ++ptr, ++dnsData)
            *ptr = *dnsData;

        *ptr = '.';
        ++ptr;
    }
    *(--ptr) = '\0';

    return len + 1; //add the last 00 octet
}

static int get_query_url_length(char* dnsData)
{
    unsigned char l;
    int i, len = 0;

    while(*dnsData != 0) {
        l = *dnsData;
        len += l+1;

        ++dnsData;

        for(i = 0; i < l; ++i, ++dnsData)
            ;
    }

    return len + 1; //add the last 00 octet
}

//moniter dns query to get the IP of specific MAC
void handle_dns_query(struct nfq_data *pkt)
{
    char mac[64], cmd[256], ipAddr[32], saddr[32];
    char *payload;
    FILE *mac2Ip;
    
    struct nfqnl_msg_packet_hw *macAddr = nfq_get_packet_hw(pkt);
    int len = nfq_get_payload(pkt, &payload);
    struct iphdr *ipHdr = ((struct iphdr*)payload);
    unsigned char *srcIp = (unsigned char*)&ipHdr->saddr;
    
    uint32_t mark = nfq_get_nfmark(pkt);
    uint32_t insNum = mark;

    if(macAddr != NULL)
        snprintf(mac, sizeof(mac), PARCON_IP_PATH"%02x:%02x:%02x:%02x:%02x:%02x", \
                macAddr->hw_addr[0], macAddr->hw_addr[1], macAddr->hw_addr[2], \
                macAddr->hw_addr[3],macAddr->hw_addr[4], macAddr->hw_addr[5]);
    else {
        fprintf(stderr, "nfq_handler: no MAC address found in %s\n", __FUNCTION__);
        return;
    }

    if(len > 0) {
        snprintf(saddr, sizeof(saddr), "%u.%u.%u.%u", srcIp[0], srcIp[1], srcIp[2], srcIp[3]);

        if((mac2Ip = fopen(mac, "r")) != NULL) {
            fgets(ipAddr, sizeof(ipAddr), mac2Ip);
            if(strcmp(ipAddr, saddr) == 0) {
                fclose(mac2Ip);
                return;
            }
        }
#if _NFQ_DEBUG_LEVEL == 1
        printf("\nsyncing ip address of deivce_%u\n", insNum);
#endif
        mac2Ip = fopen(mac, "w");
        snprintf(ipAddr, sizeof(ipAddr), "%u.%u.%u.%u", srcIp[0], srcIp[1], srcIp[2], srcIp[3]);
        fprintf(mac2Ip, "%s", ipAddr);
        fclose(mac2Ip);

        snprintf(cmd, sizeof(cmd), "iptables -F pp_disabled_%u", insNum);
#if _NFQ_DEBUG_LEVEL == 1
        printf("system: %s\n", cmd);
#endif
        system(cmd);

        snprintf(cmd, sizeof(cmd), "iptables -A pp_disabled_%u -d %s -p tcp -m multiport --sports 80,443 -m state --state ESTABLISHED -m connbytes --connbytes 0:5 --connbytes-dir reply --connbytes-mode packets -j GWMETA --dis-pp", insNum, ipAddr);
#if _NFQ_DEBUG_LEVEL == 1
        printf("system: %s\n", cmd);
#endif
        system(cmd);

        snprintf(cmd, sizeof(cmd), "iptables -F device_%u_container", insNum);
#if _NFQ_DEBUG_LEVEL == 1
        printf("system: %s\n", cmd);
#endif
        system(cmd);
        
        snprintf(cmd, sizeof(cmd), "iptables -A device_%u_container -d %s -j wan2lan_dnsr_nfqueue_%u", insNum, ipAddr, insNum);
#if _NFQ_DEBUG_LEVEL == 1
        printf("system: %s\n", cmd);
#endif
        system(cmd);
    }
    else
        fprintf(stderr, "nfq_handler: error during nfq_get_payload() in %s\n", __FUNCTION__);
}

void handle_dns_response(char *payload, uint32_t mark)
{
    char *dnsHdr = get_dns_header(payload);
    char *dnsData = dnsHdr + sizeof(struct dns_header);
    char *dnsAns;
    
    char url[512];
    char cmd[256];
    char ipAddr[INET6_ADDRSTRLEN];
    int ansNum = 0, queryNameLen = 0, i;
    __u16 type, dataLen;

    uint32_t insNum = mark & 0xff;

#if _NFQ_DEBUG_LEVEL >= 1
    queryNameLen = get_query_url(url, dnsData);
#else 
    queryNameLen = get_query_url_length(dnsData);
#endif

    type = ntohs(*(__u16 *)(dnsData + queryNameLen));

#if _NFQ_DEBUG_LEVEL == 2
    printf("type of query in answer is %d\n", type);
#endif

    //only handle DNS response with Answer RRs > 0 and query Type = A or Type = AAAA(0x001c)
    if((ansNum = ntohs(((struct dns_header*)dnsHdr)->answerRR)) > 0 && (type == 1 || type == 0x001c)) {

#if _NFQ_DEBUG_LEVEL == 2
        printf("dnsNum of query in answer is %d\n", ansNum);
#endif

        dnsAns = dnsData + queryNameLen + 2 + 2; //Type and Class fields are both 2-byte

#if _NFQ_DEBUG_LEVEL == 2
        printf("dnsAns is %x\n", *dnsAns & 0xff);
#endif

        for(i = 0; i < ansNum; i++) {

            type = ntohs(((struct dns_answer *)dnsAns)->type);
            dataLen = ntohs(((struct dns_answer *)dnsAns)->len);

            if(type == 1){
#if _NFQ_DEBUG_LEVEL == 2
                printf("type of answer in answer is %d\n", type);
                printf("dataLen of answer in answer is %x\n", dataLen);
#endif       

                unsigned char *ip = (unsigned char*)(dnsAns + sizeof(struct dns_answer));

                snprintf(ipAddr, sizeof(ipAddr), "%u.%u.%u.%u", ip[0], ip[1], ip[2], ip[3]);
                snprintf(cmd, sizeof(cmd), "ipset -! add %u %s", insNum, ipAddr);

#if _NFQ_DEBUG_LEVEL == 1
                printf("%s - %s\n", url, ipAddr);
                printf("system(\"%s\")\n", cmd);
#endif
                system(cmd);
            }else if (type == 0x001c){ /* Type AAAA*/
#if _NFQ_DEBUG_LEVEL == 2
                printf("type of answer in answer is %d\n", type);
                printf("dataLen of answer in answer is %x\n", dataLen);
#endif       
                unsigned char *ip = (unsigned char*)(dnsAns + sizeof(struct dns_answer));

                snprintf(ipAddr, sizeof(ipAddr), "%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x", \
                        ip[0], ip[1], ip[2], ip[3], ip[4], ip[5], ip[6], ip[7], ip[8], ip[9], ip[10], ip[11], ip[12], ip[13], ip[14], ip[15]);
                snprintf(cmd, sizeof(cmd), "ipset -! add %u_v6 %s", insNum, ipAddr);
#if _NFQ_DEBUG_LEVEL == 2 
                printf("%s - %s\n", url, ipAddr);
                printf("system(\"%s\")\n", cmd);
#endif
                system(cmd);
            }

            dnsAns += sizeof(struct dns_answer) + dataLen;
        }
        return;
    }
}

//packet processing function
static int dns_query_callback(struct nfq_q_handle *queueHandle, struct nfgenmsg *nfmsg, struct nfq_data *pkt, void *data)
{
    int id;
    struct nfqnl_msg_packet_hdr *ph = nfq_get_msg_packet_hdr(pkt);

    if (ph)
        id = ntohl(ph->packet_id);

    handle_dns_query(pkt);

    return nfq_set_verdict(queueHandle, id, NF_ACCEPT, 0, NULL);
}

//packet processing function
static int dns_response_callback(struct nfq_q_handle *queueHandle, struct nfgenmsg *nfmsg, struct nfq_data *pkt, void *data)
{
    int id;
    struct nfqnl_msg_packet_hdr *ph = nfq_get_msg_packet_hdr(pkt);
    char *payload;
    int len = nfq_get_payload(pkt, &payload);

    if (ph)
        id = ntohl(ph->packet_id);

    if(len > 0) 
        handle_dns_response(payload, nfq_get_nfmark(pkt));
    else
        fprintf(stderr, "nfq_handler: error during nfq_get_payload() in %s\n", __FUNCTION__);

    return nfq_set_verdict(queueHandle, id, NF_ACCEPT, 0, NULL);
}

//packet processing function
static int http_get_callback(struct nfq_q_handle *queueHandle, struct nfgenmsg *nfmsg, struct nfq_data *pkt, void *data)
{
    int id, ret = -1;
    struct nfqnl_msg_packet_hdr *ph = nfq_get_msg_packet_hdr(pkt);
    char *payload;
    char dstMac[64];
    int len = nfq_get_payload(pkt, &payload);
    
    uint32_t mark = nfq_get_nfmark(pkt);
    uint32_t insNum = mark;
    char dstIpAddr[INET6_ADDRSTRLEN], srcIpAddr[INET6_ADDRSTRLEN];
    char cmd[256];
    struct tcphdr *tcpHdr;
    int family;

    struct nfqnl_msg_packet_hw *macAddr = nfq_get_packet_hw(pkt);
    if(macAddr != NULL)
        snprintf(dstMac, sizeof(dstMac), "%02x:%02x:%02x:%02x:%02x:%02x", \
                macAddr->hw_addr[0], macAddr->hw_addr[1], macAddr->hw_addr[2], \
                macAddr->hw_addr[3],macAddr->hw_addr[4], macAddr->hw_addr[5]);

    if (ph)
        id = ntohl(ph->packet_id);

    if(len > 0) {
        struct iphdr *ipHdr = (struct iphdr*)payload;
        if (ipHdr->version == 4){
            family = AF_INET;
            unsigned char *dstIp = (unsigned char*)&ipHdr->daddr;
            unsigned char *srcIp = (unsigned char*)&ipHdr->saddr;
            tcpHdr = (struct tcphdr *)(payload + ipHdr->ihl * 4);

        snprintf(dstIpAddr, sizeof(dstIpAddr), "%u.%u.%u.%u", dstIp[0], dstIp[1], dstIp[2], dstIp[3]);
        snprintf(srcIpAddr, sizeof(srcIpAddr), "%u.%u.%u.%u", srcIp[0], srcIp[1], srcIp[2], srcIp[3]);
        if(insNum != 0){ 
            snprintf(cmd, sizeof(cmd), "ipset -! add %u %s", insNum, dstIpAddr);
            system(cmd);
        }
        
#if _NFQ_DEBUG_LEVEL == 2
        printf("\nip tot len is %u\n", ntohs(ipHdr->tot_len));
        printf("tcp hdr len is %u\n", tcpHdr->doff * 4);
        printf("ip hdr len is %u\n", ipHdr->ihl * 4);
        printf("recv tcp seq is %u\n", ntohl(tcpHdr->seq));
        printf("recv tcp ack is %u\n", ntohl(tcpHdr->ack_seq));
#endif
        }else{/* IPv6 */
            family = AF_INET6;
            struct ip6_hdr *ipv6Hdr = (struct ip6_hdr*)payload;
            struct in6_addr *daddr = &(ipv6Hdr->ip6_dst);
            struct in6_addr *saddr = &(ipv6Hdr->ip6_src);
            tcpHdr = (struct tcpHdr *)(payload + sizeof(struct ip6_hdr)); 
            inet_ntop(AF_INET6, daddr, dstIpAddr, sizeof(dstIpAddr));
            inet_ntop(AF_INET6, saddr, srcIpAddr, sizeof(srcIpAddr));
            snprintf(cmd, sizeof(cmd), "ipset -! add %u_v6 %s", insNum, dstIpAddr);
            system(cmd);
#if _NFQ_DEBUG_LEVEL == 2
            printf("\nip daddr is  %s\n", dstIpAddr);
            printf("tcp hdr len is %u\n", tcpHdr->doff * 4);
            //printf("ip hdr len is %u\n", ipHdr->ihl * 4);
            printf("recv tcp seq is %u\n", ntohl(tcpHdr->seq));
            printf("recv tcp ack is %u\n", ntohl(tcpHdr->ack_seq));
#endif
       }
        

        char *httpHdr = (char *)tcpHdr + tcpHdr->doff * 4;

        if(httpHdr[0] == 'G' && httpHdr[1] == 'E' && httpHdr[2] == 'T') {

            while (*httpHdr != 'H' || *(httpHdr+1) != 'o'|| *(httpHdr+2) != 's'|| *(httpHdr+3) != 't')
                httpHdr++;

            char *urlStart = httpHdr + strlen("Host: ");
            char *urlEnd = urlStart;
            int urlLen = 0;

            while (*urlEnd != 0x0d || *(urlEnd+1) != 0x0a)
                urlEnd++;

            urlLen = urlEnd - urlStart;

            char url[256];
            memcpy(url, urlStart, urlLen);
            url[urlLen] = '\0';
            
            unsigned long ackNum = ntohs(ipHdr->tot_len) - tcpHdr->doff * 4 - ipHdr->ihl * 4 + ntohl(tcpHdr->seq);

#if _NFQ_DEBUG_LEVEL == 1
            printf("sending pkt %s:%u ---> %s:%u\n", dstIpAddr, ntohs(tcpHdr->dest), srcIpAddr, ntohs(tcpHdr->source));
#endif
            //snprintf(cmd, sizeof(cmd), "a.out brlan0 %s %s %s %u %u %lu %lu %s", \
                    mac, dstIpAddr, srcIpAddr, ntohs(tcpHdr->dest), ntohs(tcpHdr->source), ntohl(tcpHdr->ack_seq), ackNum, url);
            //printf("cmd is %s\n", cmd);
            //system(cmd);

            //reverse src/dst ip & port

            send_tcp_pkt("brlan0", family, srcMac, dstMac, dstIpAddr, srcIpAddr, ntohs(tcpHdr->dest), ntohs(tcpHdr->source), ntohl(tcpHdr->ack_seq), ackNum, url, 1);

            ret = nfq_set_verdict(queueHandle, id, NF_DROP, 0, NULL);
        }
        else
            ret = nfq_set_verdict(queueHandle, id, NF_ACCEPT, 0, NULL);
    }
    else
        fprintf(stderr, "nfq_handler: error during nfq_get_payload() in %s\n", __FUNCTION__);

    return ret;
}
void getIFMac(char *interface, char *mac){
    int s;
    struct ifreq buffer;
    int ret = -1;
    do{
        s = socket(PF_INET, SOCK_DGRAM, 0);
        memset(&buffer, 0x00, sizeof(buffer));
        strcpy(buffer.ifr_name, interface);
        ret = ioctl(s, SIOCGIFHWADDR, &buffer);
        close(s);
        sleep(5);
    }while(ret != 0);
    strcpy(mac, (void *)ether_ntoa((struct ether_addr *)(buffer.ifr_hwaddr.sa_data)));
    return 0;
}
//skeleton to connect to iptables NFQUEUE argv[1]
//argv[2] query:intercept dns query, response:intercept dns response
int main(int argc, char *argv[])
{
    struct nfq_handle *nfqHandle;
    struct nfq_q_handle *queueHandle;
    int fd, rv;
    char buf[4096];
    u_int16_t family = AF_INET;
    int (*callback)(struct nfq_q_handle *, struct nfgenmsg *, struct nfq_data *, void *);

    if(strcmp("dns_query", argv[2]) == 0)
        callback = dns_query_callback;
    else if(strcmp("dns_response", argv[2]) == 0)
        callback = dns_response_callback;
    else if(strcmp("dnsv6_response", argv[2]) == 0){
        callback = dns_response_callback;
        family = AF_INET6;
    }else if(strcmp("http_get", argv[2]) == 0) {
        callback = http_get_callback;
        if(argc == 4)
            strncpy(srcMac, argv[3], sizeof(srcMac));
        else{
            /* In ARES/XB3 brlan0 has not been created when program started
             * Get Mac by self */
            getIFMac("brlan0", srcMac);
        }
    }else if(strcmp("httpv6_get", argv[2]) == 0) {
        callback = http_get_callback;
        family = AF_INET6;
        callback = http_get_callback;
        if(argc == 4)
            strncpy(srcMac, argv[3], sizeof(srcMac));
        else{
            /* In ARES/XB3 brlan0 has not been created when program started
             * Get Mac by self */
            getIFMac("brlan0", srcMac);
        }

    }else {
        fprintf(stderr, "nfq_handler: error during nfq_create_queue()\n");
        exit(1);
    }


    nfqHandle = nfq_open();
    if (!nfqHandle) {
        fprintf(stderr, "nfq_handler: error during nfq_open()\n");
        exit(1);
    }

    printf("unbinding existing nf_queue handler for AF_INET (if any)\n");
    if (nfq_unbind_pf(nfqHandle, family) < 0) {
        fprintf(stderr, "nfq_handler: error during nfq_unbind_pf()\n");
        exit(1);
    }

    printf("binding nfnetlink_queue as nf_queue handler for AF_INET\n");
    if (nfq_bind_pf(nfqHandle, family) < 0) {
        fprintf(stderr, "nfq_handler: error during nfq_bind_pf()\n");
        exit(1);
    }

    printf("binding this socket to queue %s in %s mode\n", argv[1], argv[2]);
    queueHandle = nfq_create_queue(nfqHandle,  atoi(argv[1]), callback, NULL);
    if (!queueHandle) {
        fprintf(stderr, "nfq_handler: error during nfq_create_queue()\n");
        exit(1);
    }

    printf("setting copy_packet mode\n");
    if (nfq_set_mode(queueHandle, NFQNL_COPY_PACKET, 0xffff) < 0) {
        fprintf(stderr, "can't set packet_copy mode\n");
        exit(1);
    }

    fd = nfq_fd(nfqHandle);

    while ((rv = recv(fd, buf, sizeof(buf), 0)) >= 0) {
#if _NFQ_DEBUG_LEVEL == 2
        printf("nfq_handler: %s packet received\n", argv[2]);
#endif
        nfq_handle_packet(nfqHandle, buf, rv);
    }

    return 0;
}