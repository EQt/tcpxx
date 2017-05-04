Transport Driver Interface (TDI)
--------------------------------

https://msdn.microsoft.com/en-us/library/windows/hardware/ff565685(v=vs.85).aspx


libuv
-----

`src/win/winsock.[ch]`:

```C
void uv_winsock_init() {}

```

Most work is done in `src/win/tcp.c`: see
- `uv_tcp_write`
- `uv_process_tcp_read_req`
- `uv_process_tcp_write_req`
- `uv_process_tcp_connect_req`
  Called from `uv__tcp_connect`.
  Calls `uv_tcp_try_connect`.
  From there, `uv_get_connectex_function` is called, which finally invokes
  [`WSAIoctl`](https://msdn.microsoft.com/de-de/library/windows/desktop/ms741394(v=vs.85).aspx) with [`guid == WSAID_CONNECTEX`](https://msdn.microsoft.com/de-de/library/windows/desktop/bb736550.aspx).
  
  
