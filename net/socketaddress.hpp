#ifndef SOCKET_ADDRESS_H
#define SOCKET_ADDRESS_H

#include <netinet/in.h>
#include <arpa/inet.h>
#include <string>
#include <cstring>

namespace net {
	class socketaddress {
		protected:
			int port;
			std::string address;

		public:
			/**
			 * Creates a new socketaddress instance based on a sockaddr_in structure
			 * @param the sockaddr_in structure
			 */
			socketaddress(struct sockaddr_in addr) {
				port = addr.sin_port;

				char ip[INET_ADDRSTRLEN];
				inet_ntop(addr.sin_family, &(addr.sin_addr), ip, INET_ADDRSTRLEN);

				address = std::string(ip);
			}

			/**
			 * Creates a new socketaddress instance with a specified address and port
			 * @param the address of the socket
			 * @param the port
			 */
			socketaddress(std::string address, int port) {
				this->address = address;
				this->port = port;
			}

			/**
			 * Returns a sockaddr_in structure based on the information of the socketaddress instance
			 * @return sockaddr_in structure
			 */
			struct sockaddr_in get_struct() {
				struct sockaddr_in addr;
				memset(&addr, 0, sizeof addr);

				addr.sin_family = AF_INET;
				addr.sin_port = htons(port);

				inet_aton(address.c_str(), &addr.sin_addr);

				return addr;
			}

			/**
			 * Gets the port of the socket
			 * @return the port number
			 */
			int get_port() {
				return port;
			}

			/**
			 * Gets the address of the socket
			 * @return the address
			 */
			std::string get_address() {
				return address;
			}
	};
};
#endif
