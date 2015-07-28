#     --    Client

add_library(url    URL.cc)
add_library(client Client.cc Timer.cc)
add_library(cli    Cli.cc)

add_executable(yahttp-client main.cc)

include_directories(yahttp-client "${yahttp-parser_SOURCE_DIR}/includes")

target_link_libraries(yahttp-client
  cli
  url
  client
  yahttpparser
)

