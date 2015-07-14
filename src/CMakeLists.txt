add_library(client Client.cc)
add_executable(yahttp-client main.cc)

target_link_libraries(yahttp-client
  client
)

