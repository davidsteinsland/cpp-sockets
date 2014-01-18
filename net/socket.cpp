#include <net/socket.hpp>
#include <string>
#include <fcntl.h>

#define DEFAULT_SOCKET_BUFFER 128

net::socket::~socket() {
	delete sockaddr;
	close();
}

void net::socket::set_blocking() {
	int opts = fcntl(socketfd, F_GETFL);
	opts = opts & (~O_NONBLOCK);
	fcntl(socketfd, F_SETFL, opts);
}

void net::socket::set_unblocking() {
	fcntl(socketfd, F_SETFL, O_NONBLOCK);
}

int net::socket::read(std::string& msg) {
	int bytes_total = 0;
	char buffer[DEFAULT_SOCKET_BUFFER];

	int bytes_read = recv(socketfd, buffer, DEFAULT_SOCKET_BUFFER, 0);

	if (bytes_read <= 0) {
		return bytes_read;
	}

	msg.append(std::string(buffer, 0, bytes_read));
	bytes_total += bytes_read;

	// set non-blocking.
	set_unblocking();

	while (bytes_read > 0) {
		memset(buffer, 0, DEFAULT_SOCKET_BUFFER);
		bytes_read = recv(socketfd, buffer, DEFAULT_SOCKET_BUFFER, 0);

		if (bytes_read < 0) {
			break;
		}

		msg.append(std::string(buffer, 0, bytes_read));
		bytes_total += bytes_read;
	}

	// set back to blocking
	set_blocking();

	return bytes_total;
}

int net::socket::read(char* buf, int len) {
	return ::recv(socketfd, buf, len, 0);
}

int net::socket::send(std::string data) {
	return send(data.c_str(), data.length(), 0);
}

int net::socket::send(const char* buf, int len, int flags) {
	return ::send(socketfd, buf, len, flags);
}
