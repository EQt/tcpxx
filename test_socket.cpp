#include "socket.hpp"


int
main()
{
    try {
        Socket sock ("localhost", 5555);
        sock.send("Hello via Socket\n");
    } catch (const char *msg) {
        fprintf(stderr, "ERROR: %s\n", msg);
    } catch (std::exception &e) {
        fprintf(stderr, "ERROR Exception: %s\n", e.what());
    }

    return 0;
}
