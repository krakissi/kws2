#include "Handler.h"

using namespace std;

void chomp(char *str){
	if((str = strpbrk(str, "\r\n")))
		*str = 0;
}

Handler::Handler(Socket *sock, int port, Configurator *cfg){
	this->sock = sock;
	this->port = port;
	this->cfg = cfg;
}

// The number of times to attempt to read from the network socket before
// closing the connection handler, with the delay between attempts in
// milliseconds.
void Handler::configure(int retries, int delay){
	this->retries = retries;

	// This value will be passed to usleep, which works on microseconds.
	this->delay = delay * 1000;
}

// Attempt to handle one HTTP transaction. Returns false if there are no more
// transactions to handle.
bool Handler::run(){
	fflush(sock->stream);

	char *str = NULL;
	size_t n;

	if(feof(sock->stream) || ferror(sock->stream))
		return false;

	int tries = 0;
	sock->block(false);
	do {
		if(getline(&str, &n, sock->stream) < 0){
			int err = errno;

			switch(err){
			case EWOULDBLOCK:
				if(tries++ >= retries)
					return false;

				clearerr(sock->stream);
				usleep(delay);
				continue;
			}
		}

		chomp(str);
	}	while(!*str);
	sock->block(true);

	// FIXME debug
	cout << str << endl;

	// TODO connection handling logic.

	free(str);
	return true;
}
