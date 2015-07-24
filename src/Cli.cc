#include "yahttp/client/Cli.hh"

namespace yahttp { namespace client {

Cli::Cli ()
{ }

Cli::~Cli ()
{ }

void Cli::show_help ()
{
  std::cout << HELP_TEXT << std::endl;
}


void Cli::parse (const int& argc, char **argv)
{
  int c;
  opterr = 0;

  while ((c = getopt (argc, argv, "p:u:h")) != -1) {
    switch (c) {
      case 'u':
        url = std::string(argv[--optind]);
        break;

      case 'p':
        optind--;
        port = std::strtoul(argv[optind], argv + std::strlen(argv[optind]), 10);
        break;

      case 'h':
        show_help();
        exit(EXIT_SUCCESS);

      case '?':
        show_help();
        if (isprint (optopt))
          fprintf(stderr, "Unknown option `-%c'.\n", optopt);
        else
          fprintf(stderr, "Unknown option character `\\x%x'.\n", optopt);

        exit(EXIT_FAILURE);
      default:
        fprintf(stderr, "Unknown case for `\\x%x'.\n", optopt);
        exit(EXIT_FAILURE);
      }
  }

  if (url.empty()) {
    show_help();
    std::cerr << "Error:" << std::endl
              << "\tURL (-u) argument must be set." << std::endl;
    exit(EXIT_FAILURE);
  }
}

}};  // ! ns yahttp client
