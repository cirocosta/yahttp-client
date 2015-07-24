#include "yahttp/URL.hh"

namespace yahttp {

URL::URL (const std::string& url)
{
  unsigned counter = 0;
  std::smatch url_match_result;
  std::smatch authority_port_match;
  std::string matched_port;

  if (std::regex_match(url, url_match_result, URL_REGEX)) {
    https = url_match_result[2] == "https";
    path = url_match_result[5];
    authority = url_match_result[4];

    if (path.empty())
      path = "/";

    std::regex_match(authority, authority_port_match,
                     AUTHORITY_PORT_REGEX);
    matched_port = authority_port_match[3];

    if (matched_port.empty()) {
      if (https)
        port = 443;
      else
        port = 80;
    } else {
      port = std::stoul(matched_port);
    }
  } else {
    throw std::runtime_error("URL::URL : Malformed URL");
  }
}

URL::~URL ()
{ }

}; // !ns yahttp

