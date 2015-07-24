# yahttp-client

> **Y**et **A**nother **http-client**: A toy C++ http client.

## build

```sh

# after clonning, recursively update dependencies

$ git submodule update --init --recursive

# create the build

$ mkdir build
$ cd build
$ cmake ..
$ make
$ ./src/yahttp-client [ADDRESS=localhost] [PORT=8080]
```

## License

GPLv2.

See `./LICENSE`.

