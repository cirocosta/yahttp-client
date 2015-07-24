#     --    Client

add_library(url    URL.cc)
add_library(client Client.cc)
add_library(cli    Cli.cc)

add_executable(yahttp-client main.cc)

target_include_directories(yahttp-client PUBLIC "${yahttp-parser_SOURCE_DIR}/includes")

target_link_libraries(yahttp-client
  cli
  url
  client
  yahttpparser
)

