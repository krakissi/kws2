#ifndef HANDLER_H
#define HANDLER_H

#include "Socket.h"

class Handler {
	SocketInfo *info;
	int port;

public:
	Handler(SocketInfo *info, int port);
	bool run();
};

#endif
