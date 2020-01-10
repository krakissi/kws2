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
	int m_sockfd;
	struct sockaddr_in m_addr;
	FILE *m_pStream;

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
