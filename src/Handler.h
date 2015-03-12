#ifndef HANDLER_H
#define HANDLER_H

#include "Socket.h"

class Handler {
	Socket *sock;
	int port;

public:
	Handler(Socket*, int);
	bool run();
};

#endif
