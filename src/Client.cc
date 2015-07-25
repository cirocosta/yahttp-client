#include "yahttp/client/Client.hh"

namespace yahttp { namespace client {

  Client::Client(const URL url)
    : m_url (url)
  {
  }

  Client::~Client()
  {
    if (m_address_info)
      freeaddrinfo(m_address_info);
  }

  int Client::init()
  {
    struct addrinfo address_hints;
    int err = 0;

    memset(&address_hints, 0, sizeof(address_hints));
    address_hints.ai_family = AF_INET;
    address_hints.ai_socktype = SOCK_STREAM;

    err = getaddrinfo(m_url.authority.c_str(), NULL,
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

  int Client::start()
  {
    struct addrinfo *res;
    int err = 0;
    char hostname[1025];

    m_server_addr.sin_family = AF_INET;
    m_server_addr.sin_port = htons(m_url.port);
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
                  << "\tAddress:" << m_url.authority << std::endl
                  << "\tIP: " << hostname << ":" << m_url.port << std::endl;
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

  std::string Client::gen_get ()
  {
    return gen_get(m_url.path);
  }

  std::string Client::gen_get (const std::string& path)
  {
    std::ostringstream actual;

    HTTPMessage msg;
    HTTPHeaderMap headers;

    headers["Host"] = m_url.authority;

    HTTPStartLinePtr sl (
      new HTTPRequestStartLine( "HTTP/1.1", HTTPMethod::GET, path)
    );

    msg.start_line = sl;
    msg.headers = headers;
    msg.type = HTTPMessageType::Request;

    actual << msg;

    return actual.str();
  }

  int Client::request(const char *message)
  {
    char buf[MAXDATASIZE];
    int numbytes = 0;
    int err;
    unsigned chunk_size = MAXDATASIZE;
    std::stringstream ss;

    if (!~(numbytes = send(m_sock_fd, message, strlen(message), 0))) {
      std::cerr << "Error in Send: " << strerror(errno) << std::endl;
      err = EXIT_FAILURE;
    }

    memset(buf, 0, MAXDATASIZE);
    while (numbytes < MAXDATASIZE) {
      if (!~(numbytes = recv(m_sock_fd, buf + numbytes, MAXDATASIZE-numbytes-1, 0))) {
        std::cerr << "Error in Recv: " << strerror(errno) << std::endl;
        err = EXIT_FAILURE;
      }
    }
    std::cout << "\t\t --- CHUNK \n\n";
    std::cout << buf;


    return err;
  }

  void Client::end()
  {
    close(m_sock_fd);
  }

  int Client::_readn (int fd, char *buffer, const int n)
  {
    char *a;
    int m, t;

    a = buffer;
    t = 0;

    while (t < n) {
      m = read(fd, a+t, n-t);
      if (m <= 0) {
        if (!t)
          return m;
        break;
      }

      t += m;
    }

    return t;
  }
}}; // !ns yahttp client

