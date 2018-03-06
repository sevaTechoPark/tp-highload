#include <iostream>
#include <fstream>
#include "../headers/Server.h"

int main() {
    try {
        int port = 80;
        string root_dir = "/var/www/html";
        int threadsCount = 256;

        std::ifstream in("/etc/httpd.conf");

        if (in.is_open()) {
            char* c = new char[100];
            std::streamsize n = 100;

            for (size_t i = 0; i < 3 && in.good(); i++) {
                in.getline(c, n);
                string data(c);
                std::size_t found = data.find_last_of('=');
                data = data.substr(found + 2);

                switch (i) {
                    case 0:
                        port = std::atoi(data.c_str());
                        break;
                    case 1:
                        threadsCount = std::atoi(data.c_str());
                        break;
                    case 2:
                        root_dir = data;
                        break;
                }
            }

            in.close();
            delete (c);
        }

        Server server(port, root_dir, threadsCount);
        server.start();
    }
    catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}