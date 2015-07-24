#ifndef YAHTPP__URL_HH
#define YAHTPP__URL_HH

#include <regex>
#include <string>
#include <iostream>

namespace yahttp {

/**
 * scheme    = $2
 * authority = $4
 * path      = $5
 * query     = $7
 * fragment  = $9
 */
const static std::regex URL_REGEX (
  R"(^(([^:\/?#]+):)?(//([^\/?#]*))?([^?#]*)(\?([^#]*))?(#(.*))?)",
  std::regex::extended
);

/**
 * authority  = $1
 * port       = $2
 */
const static std::regex AUTHORITY_PORT_REGEX (
  R"(([^:]+)(:([0-9]+))?)"
);

struct URL
{
  unsigned port;
  std::string path;
  std::string authority;
  bool https;

  URL (const std::string& url);
  ~URL ();
};

}; // ! ns yahttp

#endif
