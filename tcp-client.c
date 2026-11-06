#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "tcp-chat.h"

int main(int argc, char *argv[]) {
    int client_fd;
    struct sockaddr_in serv_addr = {0};

    if(argc != 3) {
        fprintf(stderr, "Usage: %s <IPv4 address> <port>\n", argv[0]);
        return 1;
    }

    client_fd = socket(AF_INET, SOCK_STREAM, 0);
    if(client_fd == -1) {
        perror("socket");
        return 1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons((unsigned short)atoi(argv[2]));

    if(inet_pton(AF_INET, argv[1], &serv_addr.sin_addr) != 1) {
        fprintf(stderr, "Invalid IPv4 address: %s\n", argv[1]);
        close(client_fd);
        return 1;
    }

    if(connect(client_fd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) == -1) {
        perror("connect");
        close(client_fd);
        return 1;
    }

    printf("Connected to server %s:%s. Type to chat; Ctrl-D stops sending.\n",
           argv[1], argv[2]);

    if(tcp_chat(client_fd) == -1) {
        perror("TCP chat");
        close(client_fd);
        return 1;
    }

    close(client_fd);
    return 0;
}
