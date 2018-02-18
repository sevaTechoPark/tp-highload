#include <iostream>
#include "Server.h"

int main(int argc, char **argv) {
    try {
        if (argc < 2) {
            std::cout << "Enter the port";
        }
        Server server(std::atoi(argv[1]));
        server.start();
    }
    catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}