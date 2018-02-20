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

    string typeDefinition(string);

    string mainHeaders();

public:
    const string headerNotAllowed = string("HTTP/1.1 405 Method Not Allowed\r\n");
    const string headerOk = string("HTTP/1.1 200 OK\r\n");
    const string headerNotFound = string("HTTP/1.1 404 Not Found\r\n");
    const string headerForbidden = string("HTTP/1.1 403 Forbidden\r\n");

    const string headerDate = string("Date: ");
    const string headerServer = string("Server: Seva/0.1 (Unix)\r\n");
    const string headerConnection = string("Connection: close\r\n");
    const string headerContentLength = string("Content-Length: ");

    const string contentTypeHtml = string("Content-Type: text/html\r\n");
    const string contentTypeCss = string("Content-Type: text/css\r\n");
    const string contentTypeJs = string("Content-Type: application/javascript\r\n");
    const string contentTypeGif = string("Content-Type: image/gif\r\n");
    const string contentTypeJpeg = string("Content-Type: image/jpeg\r\n");
    const string contentTypePng = string("Content-Type: image/png\r\n");
    const string contentTypeSwf = string("Content-Type: application/x-shockwave-flash\r\n");

    void get(string, string, std::function<void (const string&)>, std::function<void (int, size_t)>, bool);

    void notFound(std::function<void (const string&)>);
    void notAllowed(std::function<void (const string&)>);
    void forbidden(std::function<void (const string&)>);
};


#endif //HIGHLOAD_RESPONSE_H
