#include <iostream>
#include "Client.hh"

int main(int argc, char *argv[])
{
  http::Client connection (std::string(argv[1]), 8080);

  connection.start();
  connection.request("Hello World!");
  connection.end();

  return EXIT_SUCCESS;
}

