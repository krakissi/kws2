#ifndef HANDLER_H
#define HANDLER_H

#include "Socket.h"

#include <errno.h>
#include <unistd.h>

class Handler {
	Socket *sock;
	int port;
	int retries;
	int delay;
public:
	Handler(Socket*, int);
	void configure(int, int);
	bool run();
};

#endif
