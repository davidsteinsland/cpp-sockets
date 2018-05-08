#ifndef SOCKET_H
#define SOCKET_H

#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <string>
#include <unistd.h>
#include <cerrno>

#include <net/socketaddress.hpp>

namespace net {
	class socket {
		protected:
			int socketfd;
			struct sockaddr_in address;
			socketaddress* sockaddr;

		public:
			socket() {

			}

			/**
			 * Creates a socket instance based upon an already existing
			 * socket file descriptor and sockaddr_in structure.
			 * Used for example after a call to ::accept()
			 * @param the socket file descriptor
			 * @param the address structure
			 */
			socket(int socket, struct sockaddr_in addr) {
				socketfd = socket;
				address = addr;

				sockaddr = new socketaddress(addr);
			}

			~socket();

			/**
			 * Reads all data being sent from the client. The function will block until there's
			 * data, and then read the rest if any.
			 * @param the string object to save the data into
			 */
			int read(std::string&);

			/**
			 * Reads a specified amount of data into a character pointer
			 * @param the character buffer
			 * @param the length of the character buffer
			 */
			int read(char*, int);

			/**
			 * Sends a string to the client
			 * @param the string to send
			 */
			int send(std::string);

			/**
			 * Sends an array of charactes to the client, with a specified start and end index
			 * @param the character buffer
			 * @param the starting position
			 * @param the length
			 */
			int send(const char*, int, int);

			/**
			 * Sets the socket in blocking mode
			 */
			void set_blocking();

			/**
			 * Sets the socket in non-blocking mode
			 */
			void set_unblocking();

			/**
			 * Closes the socket connection
			 */
			void close() {
				if (socketfd == -1) {
					return;
				}

				::close(socketfd);
			}

			/**
			 * Checks whether the socket is valid
			 * @return true if the socket is valid, false otherwise
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

			/**
			 * Gets the socketaddress instance of the socket, which contains
			 * information about the socket's address and port
			 * @return the socketaddress instance
			 */
			socketaddress* get_socketaddress() {
				return sockaddr;
			}
	};
};

#endif
