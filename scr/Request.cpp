//
// Created by seva on 17.02.18.
//

#include <iostream>
#include "Request.h"

using std::string;
using std::vector;
using std::cout;
using std::endl;

string file = "/home/seva/dev/technopark/http-test-suite/httptest/160313.jpg";

Request::Request(string dir) {
    rootDir = dir;
}

void Request::parseRequest(string request, size_t size, std::function<void (const string&)> callback) {
    cout << request;

    std::istringstream iss(request);
    iss >> method;

    if (!checkMethod()) {
        callback(response.notAllowed);
    }

    iss >> url >> version;
    iss.ignore(100, '\n'); // \n after HTTP/1.1
    iss.ignore(100, '\n'); // Host: localhost:8000
    iss.ignore(100, ':');  // Accept-Encoding:
    iss >> encoding;
    iss.ignore(100, '\n'); // \n after identity
    iss.ignore(100, ':');  // Content-Length:
    iss >> contentLength;

    response.sendFile(file, callback);
}

bool Request::checkMethod() {
    return method == GET || method == HEAD;
}