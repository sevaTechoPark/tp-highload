//
// Created by seva on 17.02.18.
//

#include <iostream>
#include "../headers/Request.h"

using std::string;
using std::vector;

Request::Request(string dir): rootDir(dir) {
}

void Request::parseRequest(string request, size_t size, std::function<void (const string&)> sendHeader, std::function<void (int, size_t)> sendFile) {

    std::istringstream iss(request);
    iss >> method;

    if (!checkMethod()) {
        response.notAllowed(sendHeader);
        return;
    }

    iss >> url >> version;
    iss.ignore(100, '\n'); // \n after HTTP/1.1
    iss.ignore(100, '\n'); // Host: localhost:8000
    iss.ignore(100, ':');  // Accept-Encoding:
    iss >> encoding;
    iss.ignore(100, '\n'); // \n after identity
    iss.ignore(100, ':');  // Content-Length:
    iss >> contentLength;
    // todo: broken url
    if (method == GET) {
        response.get(rootDir, url, sendHeader, std::move(sendFile), true);
        return;
    } else if (method == HEAD) {
        response.head(rootDir, url, sendHeader);
    }

}

bool Request::checkMethod() {
    return method == GET || method == HEAD;
}