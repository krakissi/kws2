/*
	kws2
	mperron (2015)

	A web server for application developers.
*/
#include "Socket.h"
#include "Handler.h"
#include "constants.h"

#include <iostream>
#include <unistd.h>
#include <csignal>

using namespace std;

int main(int argc, char **argv){
	ListenerSocket *socket = NULL;

	// Introduce ourselves.
	cout << KWS_SERVER_NAME " is starting up!" << endl;

	// Discover the port we should bind to.
	int port = KWS_DEFAULT_PORT;
	if(argc >= 2){
		try {
			port = stoi(argv[1]);

			if(port <= 0)
				port = KWS_DEFAULT_PORT;
		} catch(...){
			cout << "Warning: Error occurred when parsing desired port." << endl;
			port = KWS_DEFAULT_PORT;
		}
	}

	// Bind the socket object, let's get cooking!
	try {
		socket = new ListenerSocket(port);
	} catch(const char *e){
		cout << "Failed: " << e << endl;
		return 1;
	}

	// Let init handle the children.
	signal(SIGCHLD, SIG_IGN);

	while(1){
		Socket *client = socket->accept_child();
		pid_t pid;
		
		if(!client)
			cout << "An error occurred when attempting to connect a client." << endl;
		else if(!(pid = fork())){
			// We're the child process, close our handle to the parent's listening socket.
			socket->close();

			Handler *handler = new Handler(client, port);
			while(handler->run());

			// End of the child process.
			client->close_socket();
			exit(0);
		}

		// The child process is handling this socket.
		client->close_socket();
	}

	return 0;
}
