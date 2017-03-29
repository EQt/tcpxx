# How is done in CPython?

Dynamically loadable module called `_socket`.
Under Windows, it is located in the `<Conda>\DLLs` directory.
Under Linux, `<Conda>/pkgs/python-3.5.2-0/lib/python3.5/lib-dynload/_socket.so` (my current python version).

