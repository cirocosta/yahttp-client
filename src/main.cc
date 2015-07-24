#include <sstream>
#include <string>
#include <iostream>
#include <regex>

#include "yahttp/client/Client.hh"
#include "yahttp/HTTP.hh"
#include "yahttp/client/Cli.hh"

using namespace yahttp;
using namespace yahttp::client;

int main(int argc, char *argv[])
{
  Cli cli;
  cli.parse(argc, argv);

  return EXIT_SUCCESS;
}

