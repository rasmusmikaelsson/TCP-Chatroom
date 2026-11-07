# TCP Chatroom
A simple TCP-based chat application written in C that allows a server and clients to communicate over a network using TCP sockets.

## Introduction
The application consists of two programs: tcp-server and tcp-client.

### TCP Server
The tcp-server program starts a TCP server on a specified port and listens for incoming client connections.

- Notifies the server when a client connects.
- Allows the server to send and receive messages.
- Currently designed to support one client at a time.

### TCP Client
The tcp-client program connects to a TCP server using a specified IP address and port.

- Establishes a connection to the specified server.
- Allows users to send messages to the server.
- Receives and displays messages from the server.


## Getting Started
### Prerequisites
To compile and run the application, you will need:

- A C compiler, such as GCC.
- GNU Make.
- A terminal environment that supports TCP sockets.

### Compilation
Clone the repository and navigate to the project directory. Then compile both programs using: `make all`

This generates two executables:

- tcp-server
- tcp-client

### Running the Application
1. Start the server

Open a terminal and run: `./tcp-server <port>`. Replace `<port>` with the port number on which the server should listen.

2. Connect a client

Open another terminal and run: `./tcp-client <server-ip> <port>`. Replace `<server-ip>` with the server's IP address and `<port>` with the port used by the server.

3. Start chatting

Once the connection is established, messages can be exchanged between the server and client through their respective terminals.

## Current Limitations
- The application is primarily designed for communication between one server and one client.
- Multiple client connections are not fully supported.
- Messages sent by the server may be received by all connected clients.

## Technologies
- Language: C
- Protocol: TCP/IP
- Networking: POSIX sockets
- Build system: GNU Make