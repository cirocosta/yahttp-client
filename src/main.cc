#include <sstream>
#include <iostream>

#include "yahttp/Client.hh"
#include "yahttp/HTTP.hh"

using namespace yahttp;

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
  http::Client connection (std::string(argv[1]), 8080);
  connection.start();
  connection.request(make_message().c_str());
  connection.end();

  return EXIT_SUCCESS;
}

