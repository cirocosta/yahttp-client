/* #include <iostream> */
/* #include <string> */
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <arpa/inet.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/socket.h>

#include "CHK.h"

#define PORT 8080
#define MAXDATASIZE 100

/* class Connection */
/* { */
/*   struct hostent* m_he; */
/*   struct sockaddr_in m_server_addr; */
/*   char m_buf[MAXDATASIZE]; */
/*   int m_numbytes; */
/*   std::string m_address; */

/* public: */
/*   Connection(const std::string address, unsigned int port); */
/*   ~Connection(); */

/*   void start() */
/*   { */

/*   } */
/*   void request(); */
/*   void end(); */

/* private: */
/*   void _init() */
/*   { */
/*     CHKNULL_H( */
/*         m_he = gethostbyname(m_address), */
/*         "gethostbyname" */
/*     ); */
/*   } */
/* }; */


int main(int argc, char *argv[])
{
  int sock_fd, numbytes;
  char buf[MAXDATASIZE];
  struct sockaddr_in server_addr;
  struct addrinfo *address_info;
  struct addrinfo *res;
  struct addrinfo address_hints;
  int error;

  memset(&address_hints, 0, sizeof(address_hints));
  address_hints.ai_family = AF_INET;
  address_hints.ai_socktype = SOCK_STREAM;

  if (argc != 2) {
    fprintf(stderr, "usage: tcp-client address\n");
    exit(EXIT_FAILURE);
  }

  // INIT
  if ((error = getaddrinfo(argv[1], NULL, &address_hints, &address_info))) {
    if (error == EAI_SYSTEM)
      perror("getaddrinfo");
    else
      fprintf(stderr, "error in getaddrinfo: %s\n", gai_strerror(error));

    exit(EXIT_FAILURE);
  }

  CHKERR(
    sock_fd = socket(AF_INET, SOCK_STREAM, 0),
    "socket"
  );

  printf("Socket Created!\n'");

  // CONNECT
  for (res = address_info; res != NULL; res = res->ai_next) {
    char hostname[1025];

    if ((error = getnameinfo(res->ai_addr, res->ai_addrlen, hostname, 1025, NULL, 0, NI_NUMERICHOST))) {
      fprintf(stderr, "error in getnameinfo: %s", gai_strerror(error));
      continue;
    }

    if (*hostname != '\0') {
      printf("Trying connection to:\n");
      printf("\tHostname:\t %s\n", argv[1]);
      printf("\tIP Address:\t %s:%d\n", hostname, PORT);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr = ((struct sockaddr_in *)(res->ai_addr))->sin_addr;
    memset(&(server_addr.sin_zero), '\0', 8);

    if (!~connect(sock_fd, (struct sockaddr*)&server_addr, sizeof(struct sockaddr))) {
      fputs("Connect error: ", stderr);
      fputs(strerror(errno), stderr);
      fputs("\n", stderr);
      continue;
    } else {
      printf("Connection Established!\n");
      break;
    }

    fprintf(stderr, "Could'nt establish a connection.\n");
    exit(EXIT_FAILURE);
  }

  // SEND AND RECEIVE

  CHKERR(
    numbytes = recv(sock_fd, buf, MAXDATASIZE-1, 0),
    "recv"
  );
  send(sock_fd, "hello world\n", 12, 0);

  buf[numbytes] = '\0';
  printf("Received: %s\n", buf);

  // CLOSE CONNECTION
  close(sock_fd);

  // FREE ALLOCATED RESOURCES
  freeaddrinfo(address_info);
  freeaddrinfo(res);

  return 0;
}

