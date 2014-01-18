#include <net/serversocket.hpp>

net::serversocket::~serversocket() {
	close();
}

int net::serversocket::listen() {

	net::socketaddress* sockaddr = new net::socketaddress(address, port);
	struct sockaddr_in addr = sockaddr->get_struct();

	socketfd = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	if (socketfd == -1) {
		return errno;
	}

	int yes = 1;
	if (::setsockopt(socketfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) != 0) {
		close();
		return errno;
	}

	if (::bind(socketfd, (struct sockaddr*)&addr, sizeof(struct sockaddr)) != 0) {
		close();
		return errno;
	}

	if (::listen(socketfd, backlog) != 0) {
		close();
		return errno;
	}

	return 0;
}

net::socket* net::serversocket::accept() {
	struct sockaddr_in from;
	socklen_t l = sizeof(from);
	int clientfd = ::accept(socketfd, (struct sockaddr*)&from, &l);

	return new net::socket(clientfd, from);
}
