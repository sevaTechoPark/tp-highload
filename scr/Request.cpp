//
// Created by seva on 17.02.18.
//

#include <iostream>
#include "Request.h"
#include <sstream>
#include <vector>

using std::string;
using std::vector;
using std::cout;
using std::endl;

const string filedir = "/home/seva/dev/technopark/http-test-suite/httptest";
const string filename = "160313.jpg";

std::string Request::parseRequest(string request, size_t size) {
    cout << request;
    for (size_t i = 0; i < 5; i++) {
        cout << endl;
    }

    std::istringstream iss(request);
    iss >> method;

    if (!checkMethod()) {
        return string("not allowed method");
    }

    iss >> url >> version;
    iss.ignore(100, '\n'); // \n after HTTP/1.1
    iss.ignore(100, '\n'); // Host: localhost:8000
    iss.ignore(100, ':');  // Accept-Encoding:
    iss >> encoding;
    iss.ignore(100, '\n'); // \n after identity
    iss.ignore(100, ':');  // Content-Length:
    iss >> contentLength;

    cout.flush();
    return string("response :)");
}

bool Request::checkMethod() {
    return method == GET || method == HEAD;
}