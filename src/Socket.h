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

class SocketInfo {
public:
	int sockfd;
	struct sockaddr_in addr;
	FILE *stream;

	SocketInfo();
	void close_socket();
	void block(bool);
};

class Socket {
	SocketInfo *info;

public:
	Socket(int);
	SocketInfo* accept_child();
	void close();
};

#endif
