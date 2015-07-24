#ifndef YAHTTP__CLIENT__CLIENT_HH
#define YAHTTP__CLIENT__CLIENT_HH

#include <iostream>
#include <string>

#include <errno.h>
#include <arpa/inet.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/socket.h>

#include "yahttp/URL.hh"

namespace yahttp { namespace client {

#define MAXDATASIZE 1024

class Client
{
  struct sockaddr_in m_server_addr;
  struct addrinfo *m_address_info;
  std::string m_address;
  unsigned int m_port;

  char m_buf[MAXDATASIZE];
  int m_numbytes;
  int m_sock_fd;

public:
  Client(const std::string address, const unsigned int port);
  ~Client();

  int start();
  int request(const char *message);
  void end();
private:
  int _init();
};

}};  // ! ns yahttp client

#endif
