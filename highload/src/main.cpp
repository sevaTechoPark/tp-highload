#include <iostream>
#include <fstream>
#include "Server.h"

int main() {
    try {
        int port;
        string root_dir;
        int threadsCount;

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
                        root_dir = data;
                        break;
                    case 2:
                        threadsCount = std::atoi(data.c_str());
                        break;
                }
            }

            in.close();
            delete (c);
        } else {
            port = 8000;
            root_dir = "/home/seva/dev/technopark/http-test-suite";
            threadsCount = 2;
        }

        Server server(port, root_dir, threadsCount);
        server.start();
    }
    catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}