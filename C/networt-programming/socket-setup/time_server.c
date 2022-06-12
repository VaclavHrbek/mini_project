/* 
 * From the book Hands-on networt programming 
 * It's not follow book in these parts:
 *	1.	The portability is not done on Windows.
 *		In book author doing it. 
*/

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <errno.h>

#include <stdio.h>
#include <string.h>
#include <time.h>

#define SOCKET int
#define ISVALIDSOCKET(s) ((s) >= 0)
#define CLOSESOCKET(s) close(s)
#define GETSOCKETERRNO() (errno)

int main(){
#if defined(_WIN32)
	printf("Windows machine detected.\n");
	printf("This program doesn't work on Windows :D.\n");
#else
	printf("Linux machine detected.\n");
#endif
	printf("Ready to use socket API.\n");

	// ----- Figure out local address that our web server should bind to:
	printf("Configuring local address...\n");
	struct addrinfo hints;			// The hints is a hit how getaddrinfo() should
									// fill other information.
	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_INET6;		// specify we are looking for IPv4.
	hints.ai_socktype = SOCK_STREAM;	// This dictate we are using TCP
	hints.ai_flags = AI_PASSIVE;		// It tells getaddrinfo() we want 
										// it bind to wildcard address
	struct addrinfo *bind_address;
	// getaddrinfo() fills in struct addrinfo. 
	getaddrinfo(0, "8080", &hints, &bind_address);
	// ------
	
	printf("Creating socket...\n");
	SOCKET socket_listen;
	socket_listen = socket(bind_address->ai_family,
			bind_address->ai_socktype,
			bind_address->ai_protocol);
	if (!ISVALIDSOCKET(socket_listen)) {
		fprintf(stderr, "socket() failed. (%d)\n", GETSOCKETERRNO());
		return 1;
	}

	int option = 0;
	if (setsockopt(socket_listen, IPPROTO_IPV6, IPV6_V6ONLY, (void*)&option,
				sizeof(option))) {
			fprintf(stderr, "setsockopt() failed. (%d)\n", GETSOCKETERRNO());
			return 1;
	}

	printf("Binding socket to local address...\n");
	// bind returns 0 on success and non-zero on failure.
	if(bind(socket_listen, bind_address->ai_addr, bind_address->ai_addrlen)) {
		fprintf(stderr, "socket() failed. (%d)\n", GETSOCKETERRNO());
		return 1;
	}
	freeaddrinfo(bind_address);

	printf("Listening...\n");
	// Second argument is how meny connections it is allowed to queue up.
	if(listen(socket_listen, 10) < 0) {
		fprintf(stderr, "socket() failed. (%d)\n", GETSOCKETERRNO());
		return 1;
	}
	
	printf("Waiting for connection...\n");
	struct sockaddr_storage client_address;
	socklen_t client_len = sizeof(client_address);
	// accept() sleep this program until new connection is established
	SOCKET socket_client = accept(socket_listen, 
			(struct sockaddr*) &client_address, 
			&client_len);
	if(!ISVALIDSOCKET(socket_client)) {
		fprintf(stderr, "accept() failed. (%d)\n", GETSOCKETERRNO());
		return 1;
	}
	
	// optional step but good practice to log connection somewhere.
	printf("Client is connected... ");
	char address_buffer[100];
	getnameinfo((struct sockaddr*) &client_address,
			client_len, 
			address_buffer, 
			sizeof(address_buffer),
			0,
			0,
			NI_NUMERICHOST);
	printf("%s\n", address_buffer);
	
	printf("Reading request...\n");
	char request[1024];		// request buffer.
	int bytes_received = recv(socket_client, request, 1024, 0);
	if(!bytes_received > 0) {
		fprintf(stderr, "recv() failed. (%d)\n", GETSOCKETERRNO());
		return 1;
	}
	printf("Received %d bytes.\n", bytes_received);

	printf("Sending response...\n");
	const char *response =
		"HTTP/1.1 200 OK\r\n"			// HTTP header
		"Connection: close\r\n"			// server will close connection when data are sent
		"Content-Type: text/plain\r\n\r\n"	//data are text
		"Local time is: ";		// Our message
	int bytes_sent = send(socket_client, response, strlen(response), 0);
	printf("Sent %d of %d bytes.\n", bytes_sent, (int)strlen(response));

	time_t timer;
	time(&timer);
	char *time_msg = ctime(&timer);
	bytes_sent = send(socket_client, time_msg, strlen(time_msg), 0);
	printf("Sent %d of %d bytes.\n", bytes_sent, (int)strlen(time_msg));

	// If connection is not close the browser will wait for another data.
	printf("Closing connection...\n");
	CLOSESOCKET(socket_client);
	
	// Now call accept another connection using accept(). The real server.
	// We close listening socket too terminate program.
	
	printf("Closing listening socket...\n");
	CLOSESOCKET(socket_listen);

	printf("Finished.\n");
	return 0;

	
	return 0;
}
