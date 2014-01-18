#include <iostream>
#include <string>
#include <net/serversocket.hpp>
#include <net/socket.hpp>
#include <cstring>

#include <thread>

void worker(net::socket* client) {
	std::cout << "Got a client!" << std::endl;

	net::socketaddress* addr = client->get_socketaddress();
	std::cout << addr->get_address() << ":" << addr->get_port() << std::endl;

	while (true) {
		std::string msg;
		if (client->read(msg) <= 0) {
			break;
		}

		std::cout << msg;
	}

	delete client;
	std::cout << "Client disconnected" << std::endl;
}

int main(void) {
	net::serversocket* server = new net::serversocket(8080);

	int err = server->listen();

	if (err != 0) {
		std::cout << strerror(err) << std::endl;
		exit(err);
	}

	while (true) {
		net::socket* client = server->accept();

		if (!client->valid()) {
			delete client;
			continue;
		}

		std::thread* t = new std::thread(worker, client);
	}

	delete server;

	return 0;
}
