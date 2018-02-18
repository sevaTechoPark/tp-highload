//
// Created by seva on 18.02.18.
//

#ifndef HIGHLOAD_RESPONSE_H
#define HIGHLOAD_RESPONSE_H

#include <string>
using std::string;

class Response {
public:
    const string notAllowed = string("HTTP/1.1 405 Method Not Allowed");
    const string ok = string("HTTP/1.1 200 OK");
    const string notFound = string("HTTP/1.1 404 Not Found");
};


#endif //HIGHLOAD_RESPONSE_H
