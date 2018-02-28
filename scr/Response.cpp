//
// Created by seva on 18.02.18.
//

#include "Response.h"
#include "boost/filesystem/operations.hpp"
#include "boost/filesystem/path.hpp"
#include "boost/progress.hpp"
#include "boost/algorithm/string.hpp"
#include <boost/lexical_cast.hpp>
#include "boost/date_time/time_facet.hpp"
#include "boost/date_time/date_facet.hpp"
#include <boost/date_time/posix_time/posix_time.hpp>
#include <fstream>
#include <boost/filesystem/fstream.hpp>

namespace fs = boost::filesystem;

string urlDecode(const std::string &in) {
    string out;
    for (std::size_t i = 0; i < in.size(); ++i) {
        if (in[i] == '%') {
            if (i + 3 <= in.size()) {
                int value = 0;
                std::istringstream is(in.substr(i + 1, 2));
                if (is >> std::hex >> value) {
                    out += static_cast<char>(value);
                    i += 2;
                }
                else {
//                    return false;
                }
            }
            else {
//                return false;
            }
        }
        else if (in[i] == '+') {
            out += ' ';
        }
        else {
            out += in[i];
        }
    }
    return out;
}

string removeQuery(const std::string &path) {
    std::size_t found = path.find_last_of('?');
    string type = path.substr(0, found);
    return type;
}

const std::string currentDateTime() {
    time_t now = time(0);
    struct tm tstruct;
    char buf[80];
    tstruct = *localtime(&now);
    strftime(buf, sizeof(buf), "%a, %d %B %Y %X GMT", &tstruct);

    return buf;
}

void Response::get(string rootDir, string path, std::function<void (const string&)> sendHeader, std::function<void (int, size_t)> sendFile, bool flag) {
    path = urlDecode(path);
    path = removeQuery(path);

    fs::path relativePath(rootDir + path);
    bool dirExist = false;
    if (is_directory(relativePath)) { // Directory index file name index.html
        relativePath /= "index.html";
        dirExist = true;
    }

    boost::system::error_code ec;
    fs::path absolutePath = canonical(relativePath, rootDir, ec);
    if (ec) {
        if (dirExist) {
            forbidden(sendHeader); // this dir exist but file index.html does not exist
        } else {
            notFound(sendHeader); // this file/dir does not exist
        }
        return;
    }

    if(!checkRootDir(absolutePath.string(), rootDir)) {
        notFound(sendHeader); // this file over the root_path
        return;
    }

    boost::uintmax_t filesize = file_size(absolutePath, ec);

    string contentType = typeDefinition(absolutePath.string());
    string length = headerContentLength + std::to_string(filesize);

    sendHeader(headerOk + mainHeaders() + contentType + length + "\r\n\r\n");
    if (flag) {
//        fs::ifstream in(absolutePath);
//
//        char buffer[16384];
//        while (size_t count = (size_t)in.readsome(buffer, 16384)) {
//            sendHeader(std::string(buffer, count));
//        }
        int fd = open(absolutePath.c_str(), O_RDONLY | O_NONBLOCK | O_ASYNC);
        sendFile(fd, filesize);
        close(fd);
    }
}

bool Response::checkRootDir(string rootDir, string path) {
    return boost::algorithm::contains(rootDir, path);
}

string Response::typeDefinition(string file) {
    std::size_t found = file.find_last_of('.');

    string type = file.substr(found + 1);

    if (type == string("html")) {
        return contentTypeHtml;
    }

    if (type == string("txt")) {
        return contentTypeHtml;
    }

    if (type == string("css")) {
        return contentTypeCss;
    }

    if (type == string("gif")) {
        return contentTypeGif;
    }

    if (type == string("jpeg")) {
        return contentTypeJpeg;
    }

    if (type == string("jpg")) {
        return contentTypeJpeg;
    }

    if (type == string("js")) {
        return contentTypeJs;
    }

    if (type == string("png")) {
        return contentTypePng;
    }

    if (type == string("swf")) {
        return contentTypeSwf;
    }

    return contentTypeHtml;
}

void Response::notFound(std::function<void (const string&)> sendHeader) {
    sendHeader(headerNotFound + mainHeaders());
}

void Response::notAllowed(std::function<void(const string &)> sendHeader) {
    sendHeader(headerNotAllowed + mainHeaders());
}

void Response::forbidden(std::function<void(const string &)> sendHeader) {
    sendHeader(headerForbidden + mainHeaders());
}

string Response::mainHeaders() {
    string currentDate = headerDate + currentDateTime() + "\r\n"; // Wed, 21 Oct 2015 07:28:00 GMT
    return currentDate + headerServer + headerConnection;
}