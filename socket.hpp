// http://www.cs.rpi.edu/~moorthy/Courses/os98/Pgms/socket.html
// https://msdn.microsoft.com/en-us/library/windows/desktop/ms738520(v=vs.85).aspx
#pragma once
#include <string>
#include <stdexcept>
#include <cstring>
#include <cstdio>
#include <cstdarg>

#ifdef _WIN32
#  include <winsock2.h>
#  include <ws2tcpip.h>
#  include <windows.h>
#  define socketfd_t SOCKET
#  ifdef _MSC_VER
#    pragma comment(lib, "ws2_32.lib")
#  endif
#else
#  include <sys/types.h>
#  include <sys/socket.h>
#  include <netinet/in.h>
#  include <unistd.h>
#  include <netdb.h>
#  define INVALID_SOCKET -1
#  define socketfd_t int
#endif


class Socket
{
public:
    Socket(const char *ipaddr,
           short port,
           bool verbose = true,
           bool udp = false);
    ~Socket();
    size_t send(const std::string &s)
        { return send(s.c_str(), s.length()); }
    size_t send(const char *s)
        { return send(s, strlen(s)); }
    size_t send(const char *s, size_t len);
private:
    socketfd_t sfd = 0;
    bool connected = false;
    #ifdef _WIN32
    WSADATA wsaData;
    #endif
    void error(const char* format, ... );
};


Socket::Socket(const char *ipaddr,
               short port,
               bool verbose,
               bool udp)
{
    struct addrinfo hints;
    struct addrinfo *result, *rp;
    int s;
    #ifdef _WIN32
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
        error("WSAStartup");
    #endif

    /* Obtain address(es) matching host/port */
    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_UNSPEC;    /* Allow IPv4 or IPv6 */
    if (udp) {
        hints.ai_socktype = SOCK_STREAM; /* Datagram socket */
        hints.ai_protocol = IPPROTO_UDP;
    } else {
        hints.ai_socktype = SOCK_STREAM; /* Stream socket */
        hints.ai_protocol = IPPROTO_TCP; /* TCP protocol */
    }
    s = getaddrinfo(ipaddr, std::to_string(port).c_str(),
                    &hints, &result);
    if (s != 0) {
        error("getaddrinfo");
    }
    for (rp = result; rp != NULL; rp = rp->ai_next) {
        sfd = socket(rp->ai_family, rp->ai_socktype,
                     rp->ai_protocol);
        if (sfd == INVALID_SOCKET)
            continue;
        if (connect(sfd, rp->ai_addr, rp->ai_addrlen) != -1) {
            connected = true;
            break;                  /* Success */
        }
    }
    freeaddrinfo(result);

    if (connected) {
        if (verbose)
            printf("connected");
    }
    else {
        error("Could not connect to %s:%d", ipaddr, port);
    }        
}


size_t
Socket::send(const char *s, size_t len)
{
    return size_t(::send(sfd, s, len, 0));
}


void
Socket::error(const char* format, ... )
{
    #ifdef _WIN32
    WSACleanup();
    #endif
    char msg[4096];
    va_list args;
    va_start(args, format);
    vsnprintf(msg, sizeof(msg), format, args);
    va_end(args);
    throw std::runtime_error(msg);
    throw std::runtime_error("error");
}


Socket::~Socket()
{
    if (connected) {
        #ifdef _WIN32
        closesocket(sfd);
        WSACleanup();
        #else
        close(sfd);
        #endif
    }
}
