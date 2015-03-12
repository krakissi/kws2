#ifndef SOCKET_H
#define SOCKET_H

#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <cstring>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstdio>
#include <fcntl.h>

class Socket {
public:
	int sockfd;
	struct sockaddr_in addr;
	FILE *stream;

	Socket();
	void close_socket();
	void block(bool);
};

class ListenerSocket : public Socket {
public:
	ListenerSocket(int);
	Socket* accept_child();
};

#endif
