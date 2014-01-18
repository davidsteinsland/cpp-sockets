#ifndef SERVERSOCKET_H
#define SERVERSOCKET_H

#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <unistd.h>
#include <cerrno>
#include <net/socket.hpp>

namespace net {
	class serversocket {
		protected:
			int port;
			int backlog;
			std::string address;

			int socketfd;

		public:
			/**
			 * Constructs a listening socket on the specified port.
			 * The default address is 0.0.0.0 and the default backlog is 10.
			 *
			 * @param the port to listen to
			 */
			serversocket(int port) {
				this->port = port;
				backlog = 10;
				address = "0.0.0.0";
			}

			/**
			 * Constructs a listening socket on the specified port with a backlog.
			 * The default address is 0.0.0.0.
			 *
			 * @param the port to listen to
			 * @param the number of backlogs
			 */
			serversocket(int port, int backlog) {
				this->port = port;
				this->backlog = backlog;
				address = "0.0.0.0";
			}

			/**
			 * Constructs a listening socket on the specified port and address
			 * @param the port to listen to
			 * @param the number of backlogs
			 * @param the address to bind to
			 */
			serversocket(int port, int backlog, std::string address) {
				this->port = port;
				this->backlog = backlog;
				this->address = address;
			}

			~serversocket();

			/**
			 * Creates the listening socket and binds to the current port and address
			 * @return error code if there was a problem
			 */
			int listen();

			/**
			 * Accepts a new incomming client (blocking call).
			 * @return A client socket instance
			 */
			net::socket* accept();

			/**
			 * Closes the listening socket
			 */
			void close() {
				if (socketfd == -1) {
					return;
				}

				::close(socketfd);
			}

			/**
			 * Checks whether or not the socket is valid
			 * @return true the socket is valid, false otherwise
			 */
			bool valid() {
				return socketfd != -1;
			}

			/**
			 * Gets the socket file descriptor
			 * @return the socket file descriptor
			 */
			int get_socket() {
				return socketfd;
			}
	};
};

#endif
