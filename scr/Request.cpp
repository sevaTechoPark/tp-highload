//
// Created by seva on 17.02.18.
//

#include <iostream>
#include "Request.h"

using std::string;
using std::vector;
using std::cout;
using std::endl;

Request::Request(string dir) {
    rootDir = dir;
}

void Request::parseRequest(string request, size_t size, std::function<void (const string&)> sendHeader, std::function<void (int, size_t)> sendFile) {
//    cout << request;

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

    if (method == GET) {
        response.sendFile(rootDir, url, sendHeader, sendFile);
        return;
    } else if (method == HEAD) {
        //
    }

}

bool Request::checkMethod() {
    return method == GET || method == HEAD;
}