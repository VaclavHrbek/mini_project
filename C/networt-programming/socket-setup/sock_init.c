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
	return 0;
}
