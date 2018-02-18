#include <iostream>
#include "Server.h"

int main(int argc, char **argv) {
    try {
        if (argc < 3) {
            return 1;
        }

        Server server(std::atoi(argv[1]), string(argv[2]));
        server.start();
    }
    catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}