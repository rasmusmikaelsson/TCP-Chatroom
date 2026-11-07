#ifndef TCP_CHAT_H
#define TCP_CHAT_H

#include <errno.h>
#include <stdio.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <unistd.h>

#define BUFSIZE 2048

/*
send_data_tcp - Sends data from client to the server using
                Transmission Controll Protocol (TCP)

@socket_fd: Socket filedescriptor established
            for communication with the server
@buffer:    The data, aka the message from client to server
@lengt:     Length of data (message)

Return:     0 on success, -1 otherwise
*/
static int send_data_tcp(int socket_fd, const char *buffer, size_t length) {
    size_t sent = 0;

    // As long as there is data to send, send it
    while(sent < length) {
        ssize_t result = send(socket_fd, buffer + sent, length - sent, MSG_NOSIGNAL);
        if(result == -1 && errno == EINTR) {
            continue;
        }
        if(result == -1) {
            return -1;
        }

        sent += (size_t)result;
    }

    return 0;
}

/*
tcp_chat - Handels all communcation between the server and the client

@socket_fd: Socket filedescriptor established
            for communication with the server

Returns: 0 on success, -1 otherwise
*/
static int tcp_chat(int socket_fd) {
    int stdin_open = 1;

    // As long as client connected to server, listen and send messages/data from/to server
    while(1) {
        fd_set read_fds;
        int max_fd = socket_fd;
        int ready;

        // Prepare fd pool
        FD_ZERO(&read_fds);
        FD_SET(socket_fd, &read_fds);
        if(stdin_open) {
            FD_SET(STDIN_FILENO, &read_fds);
            if(STDIN_FILENO > max_fd) {
                max_fd = STDIN_FILENO;
            }
        }

        // Wait until at least one file descriptor is ready for reading
        ready = select(max_fd + 1, &read_fds, NULL, NULL, NULL);
        if(ready == -1) {
            if(errno == EINTR) {
                continue;
            }
            return -1;
        }

        // If stdin ready, read from stdin and send data to server
        if(stdin_open && FD_ISSET(STDIN_FILENO, &read_fds)) {
            char buffer[BUFSIZE];
            
            ssize_t length = read(STDIN_FILENO, buffer, sizeof(buffer));
            if(length == -1) {
                if(errno == EINTR) {
                    continue;
                }
                return -1;
            }

            // EOF, stop monitoring stdin and shut down the sockets sending direction.
            if(length == 0) {
                stdin_open = 0;
                if(shutdown(socket_fd, SHUT_WR) == -1) {
                    return -1;
                }
            } else if(send_data_tcp(socket_fd, buffer, (size_t)length) == -1) {
                return -1;
            }
        }

        // Otherwise, read data from socket
        if(FD_ISSET(socket_fd, &read_fds)) {
            char buffer[BUFSIZE];

            ssize_t length = read(socket_fd, buffer, sizeof(buffer));
            if(length == -1) {
                if(errno == EINTR) {
                    continue;
                }
                return -1;
            }
            if(length == 0) {
                return 0;
            }
            if(fwrite(buffer, 1, (size_t)length, stdout) != (size_t)length ||
               fflush(stdout) == EOF) {
                return -1;
            }
        }
    }
}

#endif
