#include <iostream>
#include "Server.h"

int main() {
    try {

        Server server;
        server.start();
    }
    catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}