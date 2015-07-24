#include "gtest/gtest.h"
#include "yahttp/URL.hh"

using namespace yahttp;

TEST(Url, SimpleLocalhost) {
  const std::string url_str ("http://localhost:8080");
  URL url (url_str);

  EXPECT_EQ(url.path, "/");
  EXPECT_EQ(url.authority, "localhost");
  EXPECT_EQ(url.port, 8080);
  EXPECT_EQ(url.https, false);
}

TEST(Url, HttpsLocalhostWithPath) {
  const std::string url_str ("https://localhost:8080/assets/photo.png");
  URL url (url_str);

  EXPECT_EQ(url.path, "/assets/photo.png");
  EXPECT_EQ(url.authority, "localhost");
  EXPECT_EQ(url.port, 8080);
  EXPECT_EQ(url.https, true);
}

TEST(Url, HttpsLocalhostWithoutPort) {
  const std::string url_str ("https://localhost.com.br/assets/photo.png");
  URL url (url_str);

  EXPECT_EQ(url.path, "/assets/photo.png");
  EXPECT_EQ(url.authority, "localhost.com.br");
  EXPECT_EQ(url.port, 443);
  EXPECT_EQ(url.https, true);
}

TEST(Url, LocalhostWithPathWithoutPort) {
  const std::string url_str ("http://localhost.com.br/assets/photo.png");
  URL url (url_str);

  EXPECT_EQ(url.path, "/assets/photo.png");
  EXPECT_EQ(url.authority, "localhost.com.br");
  EXPECT_EQ(url.port, 80);
  EXPECT_EQ(url.https, false);
}

TEST(Url, LocalhostWithSubdomain) {
  const std::string url_str ("http://www.localhost.com.br/");
  URL url (url_str);

  EXPECT_EQ(url.path, "/");
  EXPECT_EQ(url.authority, "www.localhost.com.br");
  EXPECT_EQ(url.port, 80);
  EXPECT_EQ(url.https, false);
}

