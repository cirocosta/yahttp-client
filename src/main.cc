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

  Client client (URL (cli.url));
  client.init();

  client.start();
  client.request(client.gen_get().c_str());
  client.end();

  return EXIT_SUCCESS;
}

