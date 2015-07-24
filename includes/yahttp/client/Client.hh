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
#include "yahttp/HTTP.hh"

namespace yahttp { namespace client {

#define MAXDATASIZE 1024

class Client
{
  struct sockaddr_in m_server_addr;
  struct addrinfo *m_address_info = nullptr;
  URL m_url;

  char m_buf[MAXDATASIZE];
  int m_numbytes;
  int m_sock_fd;

public:
  Client (const URL url);
  ~Client ();

  int start ();
  std::string gen_get ();
  std::string gen_get (const std::string& path);
  int init ();
  void end ();
private:
  int _request (const char *message);
};

}};  // ! ns yahttp client

#endif
