include_directories(${yahtml-client_INCLUDES})

add_executable(url_test url_test.cc)
add_executable(client_test client_test.cc)

add_test(NAME url_test COMMAND url_test)
add_test(NAME client_test COMMAND client_test)

target_link_libraries(url_test gtest gtest_main ${yahttp-client_LIBS})
target_link_libraries(client_test gtest gtest_main ${yahttp-client_LIBS})

