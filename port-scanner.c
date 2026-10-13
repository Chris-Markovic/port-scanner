#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>
#include <sys/socket.h>


void port_scanner(char *tIP, char *First_Port, char *Last_Port){
    int start_port = atoi(First_Port);
    int end_port = atoi(Last_Port);

    for(int port = start_port; port <= end_port; port++){
        char port_str[6];
        snprintf(port_str, sizeof(port_str), "%d", port);

        struct addrinfo hints;
        memset(&hints, 0, sizeof(hints));
        hints.ai_family = AF_INET;
        hints.ai_socktype = SOCK_STREAM;

        struct addrinfo *serv_addr;
        int err = getaddrinfo(tIP, port_str, &hints, &serv_addr);
        if(err != 0){
            printf("Port %d: error (%s)\n", port, gai_strerror(err));
            continue;
        }

        int is_open = 0;
        struct addrinfo *temp;
        for(temp = serv_addr; temp != NULL; temp = temp->ai_next){
            int sockfd = socket(temp->ai_family, temp->ai_socktype, temp->ai_protocol);
            if(sockfd < 0)
                continue;
            if(connect(sockfd, temp->ai_addr, temp->ai_addrlen) == 0){
                is_open = 1;
                close(sockfd);
                break;
            }
            close(sockfd);
        }
        if(is_open)
            printf("Port %d is open.\n", port);
        freeaddrinfo(serv_addr);
    }
}


int main(int argc, char *argv[]) {
    if (argc != 4){
        printf("Please enter a valid server IP address and range of ports to be scanned.");
        printf("USAGE: %s IPv4 First_Port Last_Port\n", argv[0]);
        exit(1);
    }
    char tIP[16] = {0};
    snprintf(tIP, sizeof(tIP), "%s", argv[1]);
    char First_Port[6] = {0};
    snprintf(First_Port, sizeof(First_Port), "%s", argv[2]);
    char Last_Port[6] = {0};
    snprintf(Last_Port, sizeof(Last_Port), "%s", argv[3]);

    //Start port scanner
    port_scanner(tIP, First_Port, Last_Port);
    return 0;
}