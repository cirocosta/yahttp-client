#include <sstream>
#include <string>
#include <iostream>
#include <regex>

#include "yahttp/client/Client.hh"
#include "yahttp/HTTP.hh"
#include "yahttp/client/Cli.hh"

using namespace yahttp;
using namespace yahttp::client;


std::string make_message ()
{
  std::ostringstream message;
  HTTPRequestStartLine req ("HTTP/1.1", HTTPMethod::POST, "/path");
  std::string body = "hue hue brbr";
  HTTPBody data (body.begin(), body.end());
  HTTPRequestMessage req_msg (
    req,
    HTTPHeaderMap {{"Content-Length", "1024"}},
    data
  );

  message << req_msg;

  return message.str();
}


int main(int argc, char *argv[])
{
  Cli cli;
  cli.parse(argc, argv);
  unsigned counter = 0;

  Client connection (cli.url, 8080);
  connection.start();
  connection.request(make_message().c_str());
  connection.end();

  return EXIT_SUCCESS;
}

