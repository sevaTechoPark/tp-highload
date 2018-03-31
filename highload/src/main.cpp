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

                std::string::iterator end_pos = std::remove(data.begin(), data.end(), ' ');
                data.erase(end_pos, data.end());

                std::size_t found = data.find_last_of('=');

                if (strstr(data.substr(0, found).c_str(), "listen")) {
                    port = std::atoi(data.substr(found + 1).c_str());
                }

                if (strstr(data.substr(0, found).c_str(), "document_root")) {
                    root_dir = data.substr(found + 1);
                }

                if (strstr(data.substr(0, found).c_str(), "cpu_limit")) {
                    threadsCount = std::atoi(data.substr(found + 1).c_str());
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