#ifndef HANDLER_H
#define HANDLER_H

#include "Socket.h"
#include "Configurator.h"

#include <errno.h>
#include <unistd.h>

class Handler {
	Socket *m_pSock;
	int m_port;
	int m_retries;
	int m_delay;
	Configurator *m_pCfg;

public:
	Handler(Socket*, int, Configurator*);
	void configure(int, int);
	bool run();
};

#endif
