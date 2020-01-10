#include "Handler.h"

using namespace std;

void chomp(char *str){
	if((str = strpbrk(str, "\r\n")))
		*str = 0;
}

Handler::Handler(Socket *sock, int port, Configurator *cfg) :
	m_pSock(sock), m_port(port), m_pCfg(cfg) {}

// The number of times to attempt to read from the network socket before
// closing the connection handler, with the delay between attempts in
// milliseconds.
void Handler::configure(int retries, int delay){
	m_retries = retries;

	// This value will be passed to usleep, which works on microseconds.
	m_delay = delay * 1000;
}

// Attempt to handle one HTTP transaction. Returns false if there are no more
// transactions to handle.
bool Handler::run(){
	fflush(m_pSock->m_pStream);

	char *str = NULL;
	size_t n;

	if(feof(m_pSock->m_pStream) || ferror(m_pSock->m_pStream))
		return false;

	int tries = 0;
	m_pSock->block(false);
	do {
		if(getline(&str, &n, m_pSock->m_pStream) < 0){
			int err = errno;

			switch(err){
			case EWOULDBLOCK:
				if(tries++ >= m_retries)
					return false;

				clearerr(m_pSock->m_pStream);
				usleep(m_delay);
				continue;
			}
		}

		chomp(str);
	} while(!*str);

	m_pSock->block(true);

	// FIXME debug
	fprintf(m_pSock->m_pStream, "echo: %s\r\n", str);
	cout << str << endl;

	// TODO connection handling logic.

	free(str);
	return true;
}
