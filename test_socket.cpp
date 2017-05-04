#include "socket.hpp"
#include <iostream>


int
main(int argc, char *argv[])
{
    try {
        bool udp = argc > 1;
        Socket sock ("localhost", 5555, true, udp);
        std::cout << sock.send("Hello via Socket\n")
                  << std::endl;
    } catch (const char *msg) {
        fprintf(stderr, "ERROR: %s\n", msg);
    } catch (std::exception &e) {
        fprintf(stderr, "ERROR Exception: %s\n", e.what());
    }

    return 0;
}
