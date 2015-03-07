#include "Handler.h"

using namespace std;

void chomp(char *str){
	if((str = strpbrk(str, "\r\n")))
		*str = 0;
}

Handler::Handler(SocketInfo *info, int port){
	this->info = info;
	this->port = port;
}

// Attempt to handle one HTTP transaction. Returns false if there are no more
// transactions to handle.
bool Handler::run(){
	fflush(info->stream);

	char *str = NULL;
	size_t n;

	if(feof(info->stream) || ferror(info->stream))
		return false;

	info->block(false);
	do {
		if(getline(&str, &n, info->stream) <= 0)
			return false;

		chomp(str);
	}	while(!*str);
	info->block(true);

	// FIXME debug
	cout << str << endl;

	// TODO connection handling logic.

	free(str);
	return true;
}
