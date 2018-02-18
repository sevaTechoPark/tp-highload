//
// Created by seva on 18.02.18.
//

#ifndef HIGHLOAD_RESPONSE_H
#define HIGHLOAD_RESPONSE_H

#include <string>
using std::string;

class Response {
public:
    string notAllowed = string("HTTP/1.1 405 Method Not Allowed");
};


#endif //HIGHLOAD_RESPONSE_H
