TCP in C++
==========

There are a lot of other libraries:

[`libsocket`](https://github.com/dermesser/libsocket), e.g.

But they are usually not designed for cross-platform usage.

Essentially, Windows and *nix systems work quite [similar](http://stackoverflow.com/a/28031039); however there are differences that matter in practice.

You might also try OpenSSL library, `libuv`,
[apache runtime (apr)](https://apr.apache.org/docs/apr/1.5/group__apr__network__io.html), or
[boost asio](TODO).
But then you will have a huge library dependency to ship with your code that is unnecessary.
Furthermore, libuv is designed as an asynchronous library, yielding in a structure that is more complicated than necessary.
