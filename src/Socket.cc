#include "Socket.h"

using namespace std;

Socket::Socket() :
	m_pStream(NULL), m_sockfd(-1)
{
	memset(&m_addr, 0, sizeof(m_addr));
}

Socket::~Socket(){
	if(m_pStream)
		fclose(m_pStream);
	if(m_sockfd > 0)
		close(m_sockfd);

	m_sockfd = -1;
	m_pStream = NULL;
}

void Socket::block(bool should){
	int mask = fcntl(m_sockfd, F_GETFL, 0);
	if(should)
		mask &= ~O_NONBLOCK;
	else
		mask |= O_NONBLOCK;
	
	fcntl(m_sockfd, F_SETFL, mask);
}

ListenerSocket::ListenerSocket(int port){
	cout << "Port requested: " << port << endl;

	// Acquire INET socket.
	if((m_sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
		throw "Socket not got.";

	m_addr.sin_family = AF_INET;
	m_addr.sin_port = htons(port);
	m_addr.sin_addr.s_addr = htonl(INADDR_ANY);

	int optval = 2;
	setsockopt(m_sockfd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval));

	if(bind(m_sockfd, (struct sockaddr*)&(m_addr), sizeof(m_addr)) == -1)
		throw "Couldn't bind.";

	if(listen(m_sockfd, 64) == -1)
		throw "Deaf.";
}

Socket* ListenerSocket::accept_child(){
	Socket *info_client = new Socket();
	int length = sizeof(info_client->m_addr);

	info_client->m_sockfd = accept(m_sockfd, (struct sockaddr*)&(info_client->m_addr), (socklen_t*)&length);
	if(info_client->m_sockfd < 0)
		return NULL;

	info_client->m_pStream = fdopen(info_client->m_sockfd, "w+");

	return info_client;
}
