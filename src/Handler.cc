#include "Handler.h"

using namespace std;

void chomp(char *str){
	if((str = strpbrk(str, "\r\n")))
		*str = 0;
}

Handler::Handler(Socket *sock, int port){
	this->sock = sock;
	this->port = port;
}

// Attempt to handle one HTTP transaction. Returns false if there are no more
// transactions to handle.
bool Handler::run(){
	fflush(sock->stream);

	char *str = NULL;
	size_t n;

	if(feof(sock->stream) || ferror(sock->stream))
		return false;

	sock->block(false);
	do {
		if(getline(&str, &n, sock->stream) <= 0)
			return false;

		chomp(str);
	}	while(!*str);
	sock->block(true);

	// FIXME debug
	cout << str << endl;

	// TODO connection handling logic.

	free(str);
	return true;
}
