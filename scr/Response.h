//
// Created by seva on 18.02.18.
//

#ifndef HIGHLOAD_RESPONSE_H
#define HIGHLOAD_RESPONSE_H

#include <boost/asio.hpp>
#include <string>
using std::string;

class Response {
private:
//    static const size_t bufferSize = 1024;
//    char buffer[bufferSize];
    bool checkRootDir(string, string);
public:
    const string notAllowed = string("HTTP/1.1 405 Method Not Allowed");
    const string ok = string("HTTP/1.1 200 OK");
    const string notFound = string("HTTP/1.1 404 Not Found");

    const string contentLength = string("Content-Length: ");

    const string contentTypeHtml = string("Content-Type: text/html");
    const string contentTypeCss = string("Content-Type: text/css");
    const string contentTypeJs = string("Content-Type: application/javascript");
    const string contentTypeGif = string("Content-Type: image/gif");
    const string contentTypeJpeg = string("Content-Type: image/jpeg");
    const string contentTypePng = string("Content-Type: image/png");

    void sendFile(string, string, std::function<void (const string&)>, std::function<void (int)>);
};


#endif //HIGHLOAD_RESPONSE_H
