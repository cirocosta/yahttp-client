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
  HTTPMessagePtr message;
  unsigned status_code;

  Cli cli;
  cli.parse(argc, argv);

  Client client (URL (cli.url));
  client.init();

  client.start();
  message = client.request(client.gen_get().c_str());

  status_code = static_cast<HTTPResponseStartLine*>(message->start_line.get())->status_code;

  switch (status_code) {
    case 200:
      std::cout << message->body << std::endl;
      break;

    default:
      std::cerr << "Error:" << std::endl
                << "\tStatus code != 200: " << status_code << std::endl;
      exit(EXIT_FAILURE);
  }

  client.end();

  return EXIT_SUCCESS;
}

