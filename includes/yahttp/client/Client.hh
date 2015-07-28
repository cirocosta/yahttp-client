#ifndef YAHTTP__CLIENT__CLIENT_HH
#define YAHTTP__CLIENT__CLIENT_HH

#include <iostream>
#include <sstream>
#include <string>

#include <errno.h>
#include <fcntl.h>
#include <arpa/inet.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/socket.h>

#include "yahttp/URL.hh"
#include "yahttp/HTTP.hh"
#include "yahttp/Timer.hh"

namespace yahttp { namespace client {

#define MAXDATASIZE 102400

class Client
{
  struct sockaddr_in m_server_addr;
  struct addrinfo *m_address_info = nullptr;
  URL m_url;

  int m_numbytes;
  int m_sock_fd;

public:
  Client (const URL url);
  ~Client ();

  int init ();
  int start ();
  int request (const char *message);
  void end ();

  std::string gen_get ();
  std::string gen_get (const std::string& path);
private:
  int _readn (int fd, char *buffer, const int n) const;
  int _recv_till_timeout(int timeout = 2);
};

}};  // ! ns yahttp client

#endif
