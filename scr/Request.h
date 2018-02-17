//
// Created by seva on 17.02.18.
//

#ifndef HIGHLOAD_REQUEST_H
#define HIGHLOAD_REQUEST_H

#include <cstdlib>

using std::string;

class Request {
public:
    string parseRequest(string, size_t);

    bool checkMethod();
private:
    string method;
    string url;
    string version;
    string encoding;
    string contentLength;

    const string GET = "GET";
    const string HEAD = "HEAD";
};


#endif //HIGHLOAD_REQUEST_H
