//
// Created by seva on 18.02.18.
//

#include "Response.h"
#include <fstream>

void Response::sendFile(string path, std::function<void (const string&)> callback) {

    std::ifstream in(path);

    while (size_t count = static_cast<size_t>(in.readsome(buffer, bufferSize))) {
        callback(std::string(buffer, count));
    }
}