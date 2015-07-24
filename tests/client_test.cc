#include "gtest/gtest.h"
#include "yahttp/URL.hh"
#include "yahttp/client/Client.hh"

using namespace yahttp;
using namespace yahttp::client;

TEST(Client, SimpleLocalhost) {
  const char* url_location = "http://localhost:8080/path";
  const char* expected_get =
    "GET /path HTTP/1.1\r\n"
    "Host: localhost:8080\r\n"
    "\r\n";

  URL url (url_location);
  Client client (url);

  std::string req_msg = client.gen_get();

  EXPECT_EQ(expected_get, req_msg);
}

