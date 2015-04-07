#ifndef HANDLER_H
#define HANDLER_H

#include "Socket.h"
#include "Configurator.h"

#include <errno.h>
#include <unistd.h>

class Handler {
	Socket *sock;
	int port;
	int retries;
	int delay;
	Configurator *cfg;

public:
	Handler(Socket*, int, Configurator*);
	void configure(int, int);
	bool run();
};

#endif
