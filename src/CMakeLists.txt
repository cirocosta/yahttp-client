#   Client Library

include_directories(${INCLUDES})

add_library(yahttpclient URL.cc Client.cc Timer.cc)
target_link_libraries(yahttpclient ${yahttp-parser_LIBS})


# Executable

add_executable(yahttp-client main.cc Cli.cc)
target_link_libraries(yahttp-client yahttpclient)


# Variables

set(LIBS "yahttpclient" PARENT_SCOPE)

