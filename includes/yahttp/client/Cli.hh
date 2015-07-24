#ifndef YAHTTP__CLIENT_CLI_HH
#define YAHTTP__CLIENT_CLI_HH

#include <iostream>
#include <unistd.h>
#include <ctype.h>
#include <cstring>


namespace yahttp { namespace client {

class Cli
{
public:
  std::string url;
  unsigned port;
public:
  Cli();
  ~Cli();

  void show_help ();
  void parse (const int& argc, char **argv);
};

static const char *HELP_TEXT =
  "Usage: ./yahttp-client -u URL [-p PORT]\n"
  "\n"
  "Options:\n"
  "  -u\turl to be queried against\n"
  "  -p\tport used\n"
  "  -h\tshow this message\n"
  "\n"
  "Examples:\n"
  "  GET a file from /path/file.png\n"
  "\t$ ./yahttp-client -u http://localhost:8080/path/file.png\n"
  "\n";

}}; // ! ns yahttp client

#endif
