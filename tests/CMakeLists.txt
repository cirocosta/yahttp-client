#     --    Configure GTEST

find_package(Threads REQUIRED)
include(ExternalProject)
ExternalProject_Add(
  gtest
  GIT_REPOSITORY https://github.com/cirocosta/googletest.git
  PREFIX ${CMAKE_CURRENT_BINARY_DIR}/gtest
  UPDATE_COMMAND ""
  INSTALL_COMMAND ""
)

add_library(libgtest IMPORTED STATIC GLOBAL)
add_dependencies(libgtest gtest)

ExternalProject_Get_Property(gtest source_dir binary_dir)
set_target_properties(libgtest PROPERTIES
    "IMPORTED_LOCATION" "${binary_dir}/libgtest.a"
    "IMPORTED_LINK_INTERFACE_LIBRARIES" "${CMAKE_THREAD_LIBS_INIT}"
)

include_directories("${source_dir}/include")
include_directories(${yahttp-parser_SOURCE_DIR}/includes)


#     --    TEST

add_executable(url_test main_test.cc url_test.cc)
target_link_libraries(url_test libgtest
  url
)

add_test(NAME url_test COMMAND url_test)

add_executable(client_test main_test.cc client_test.cc)
target_link_libraries(client_test libgtest
  url
  client
  yahttpparser
)

add_test(NAME client_test COMMAND client_test)

