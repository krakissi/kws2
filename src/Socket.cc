#include "Socket.h"

using namespace std;

Socket::Socket(){
	memset(&addr, 0, sizeof(addr));
	stream = NULL;
	sockfd = -1;
}

void Socket::close_socket(){
	if(stream)
		fclose(stream);
	if(sockfd > 0)
		close(sockfd);

	sockfd = -1;
	stream = NULL;
}

void Socket::block(bool should){
	int mask = fcntl(sockfd, F_GETFL, 0);
	if(should)
		mask &= ~O_NONBLOCK;
	else
		mask |= O_NONBLOCK;
	
	fcntl(sockfd, F_SETFL, mask);
}

ListenerSocket::ListenerSocket(int port){
	cout << "Port requested: " << port << endl;

	// Acquire INET socket.
	if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
		throw "Socket not got.";

	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	addr.sin_addr.s_addr = htonl(INADDR_ANY);

	int optval = 2;
	setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval));

	if(bind(sockfd, (struct sockaddr*)&(addr), sizeof(addr)) == -1)
		throw "Couldn't bind.";

	if(listen(sockfd, 64) == -1)
		throw "Deaf.";
}

Socket* ListenerSocket::accept_child(){
	Socket *info_client = new Socket();
	int length = sizeof(info_client->addr);

	info_client->sockfd = accept(sockfd, (struct sockaddr*)&(info_client->addr), (socklen_t*)&length);
	if(info_client->sockfd < 0)
		return NULL;

	info_client->stream = fdopen(info_client->sockfd, "w+");

	return info_client;
}

void ListenerSocket::close(){
	close_socket();
}
