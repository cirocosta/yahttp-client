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

#define PORT 8080
#define MAXDATASIZE 100

class Connection
{
  struct sockaddr_in m_server_addr;
  struct addrinfo *m_address_info;
  std::string m_address;
  unsigned int m_port;

  char m_buf[MAXDATASIZE];
  int m_numbytes;
  int m_sock_fd;

public:
  Connection(const std::string address, unsigned int port)
    : m_address(address), m_port(port)
  {
    _init();
  }

  ~Connection()
  {
    freeaddrinfo(m_address_info);
  }

  int start()
  {
    struct addrinfo *res;
    int err = 0;
    char hostname[1025];

    m_server_addr.sin_family = AF_INET;
    m_server_addr.sin_port = htons(m_port);
    memset(&(m_server_addr.sin_zero), '\0', 8);

    for (res = m_address_info; res != NULL; res = res->ai_next) {
      err = getnameinfo(res->ai_addr, res->ai_addrlen, hostname,
                        1025, NULL, 0, NI_NUMERICHOST);
      if (err) {
        std::cerr << "Error in getnameinfo: " << gai_strerror(err)
                  << std::endl;
        continue;
      }

      if (*hostname != '\0') {
        std::cout << "Trying connection to:" << std::endl
                  << "\tAddress:" << m_address << std::endl
                  << "\tIP: " << hostname << ":" << m_port << std::endl;
      }

      m_server_addr.sin_addr =
        ((struct sockaddr_in*)(res->ai_addr))->sin_addr;

      err = connect(m_sock_fd, (struct sockaddr*)&m_server_addr,
                    sizeof(struct sockaddr));
      if (!err) {
        std::cout << "Connection Established!" << std::endl;
        break;
      } else {
        std::cerr << "Connect Error: " << strerror(errno) << std::endl;
        continue;
      }

      std::cerr << "Couldn't establish a connection." << std::endl;
      err = EXIT_FAILURE;
    }

    return err;
  }

  int request(const char *message)
  {
    int numbytes;
    int err;

    if (!~(numbytes = send(m_sock_fd, message, strlen(message), 0))) {
      std::cerr << "Error in Send: " << strerror(errno) << std::endl;
      err = EXIT_FAILURE;
    }

    if (!~(numbytes = recv(m_sock_fd, m_buf, MAXDATASIZE-1, 0))) {
      std::cerr << "Error in Recv: " << strerror(errno) << std::endl;
      err = EXIT_FAILURE;
    }

    return err;
  }

  void end()
  {
    close(m_sock_fd);
  }

private:
  int _init()
  {
    struct addrinfo address_hints;
    int err = 0;

    memset(&address_hints, 0, sizeof(address_hints));
    address_hints.ai_family = AF_INET;
    address_hints.ai_socktype = SOCK_STREAM;

    err = getaddrinfo(m_address.c_str(), NULL,
                      &address_hints, &m_address_info);

    if (err) {
      if (err == EAI_SYSTEM)
        perror("getaddrinfo");
      else
        fprintf(stderr, "error in getaddrinfo: %s\n", gai_strerror(err));
      return err;
    }

    m_sock_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (!~m_sock_fd) {
      std::cerr << "socket: " << strerror(errno) << std::endl;
      return m_sock_fd;
    }

    return err;
  }
};


int main(int argc, char *argv[])
{
  Connection connection (std::string(argv[1]), 8080);
  connection.start();
  connection.request("Hello World!");
  connection.end();

  return EXIT_SUCCESS;
}

