#include "Socket.h"

using namespace std;

SocketInfo::SocketInfo(){
	memset(&addr, 0, sizeof(addr));
	stream = NULL;
	sockfd = -1;
}

void SocketInfo::close_socket(){
	if(stream)
		fclose(stream);
	if(sockfd > 0)
		close(sockfd);

	sockfd = -1;
	stream = NULL;
}

void SocketInfo::block(bool should){
	int mask = fcntl(sockfd, F_GETFL, 0);
	if(should)
		mask &= ~O_NONBLOCK;
	else
		mask |= O_NONBLOCK;
	
	fcntl(sockfd, F_SETFL, mask);
}

Socket::Socket(int port){
	cout << "Port requested: " << port << endl;

	info = new SocketInfo();

	// Acquire INET socket.
	if((info->sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
		throw "Socket not got.";

	info->addr.sin_family = AF_INET;
	info->addr.sin_port = htons(port);
	info->addr.sin_addr.s_addr = htonl(INADDR_ANY);

	int optval = 2;
	setsockopt(info->sockfd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval));

	if(bind(info->sockfd, (struct sockaddr*)&(info->addr), sizeof(info->addr)) == -1)
		throw "Couldn't bind.";

	if(listen(info->sockfd, 64) == -1)
		throw "Deaf.";
}

SocketInfo* Socket::accept_child(){
	SocketInfo *info_client = new SocketInfo();
	int length = sizeof(info_client->addr);

	info_client->sockfd = accept(info->sockfd, (struct sockaddr*)&(info_client->addr), (socklen_t*)&length);
	if(info_client->sockfd < 0)
		return NULL;

	info_client->stream = fdopen(info_client->sockfd, "w+");

	return info_client;
}

void Socket::close(){
	if(info)
		info->close_socket();
}
