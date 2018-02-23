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

namespace fs = boost::filesystem;

const char HEX2DEC[256] = {
                /*       0  1  2  3   4  5  6  7   8  9  A  B   C  D  E  F */
                /* 0 */ -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1,
                /* 1 */ -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1,
                /* 2 */ -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1,
                /* 3 */  0, 1, 2, 3,  4, 5, 6, 7,  8, 9,-1,-1, -1,-1,-1,-1,

                /* 4 */ -1,10,11,12, 13,14,15,-1, -1,-1,-1,-1, -1,-1,-1,-1,
                /* 5 */ -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1,
                /* 6 */ -1,10,11,12, 13,14,15,-1, -1,-1,-1,-1, -1,-1,-1,-1,
                /* 7 */ -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1,

                /* 8 */ -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1,
                /* 9 */ -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1,
                /* A */ -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1,
                /* B */ -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1,

                /* C */ -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1,
                /* D */ -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1,
                /* E */ -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1,
                /* F */ -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1
};

string UriDecode(const std::string & sSrc) {
    // Note from RFC1630: "Sequences which start with a percent
    // sign but are not followed by two hexadecimal characters
    // (0-9, A-F) are reserved for future extension"

    const unsigned char * pSrc = (const unsigned char *)sSrc.c_str();
    const int SRC_LEN = sSrc.length();
    const unsigned char * const SRC_END = pSrc + SRC_LEN;
    // last decodable '%'
    const unsigned char * const SRC_LAST_DEC = SRC_END - 2;

    char * const pStart = new char[SRC_LEN];
    char * pEnd = pStart;

    while (pSrc < SRC_LAST_DEC)
    {
        if (*pSrc == '%')
        {
            char dec1, dec2;
            if (-1 != (dec1 = HEX2DEC[*(pSrc + 1)])
                && -1 != (dec2 = HEX2DEC[*(pSrc + 2)]))
            {
                *pEnd++ = (dec1 << 4) + dec2;
                pSrc += 3;
                continue;
            }
        }

        *pEnd++ = *pSrc++;
    }

    // the last 2- chars
    while (pSrc < SRC_END)
        *pEnd++ = *pSrc++;

    std::string sResult(pStart, pEnd);
    delete [] pStart;
    return sResult;
}

string removeQuery(const std::string &path) {
    std::size_t found = path.find_last_of('?');
    string type = path.substr(0, found);
    return type;
}

const std::string currentDateTime() {
    time_t     now = time(0);
    struct tm  tstruct;
    char       buf[80];
    tstruct = *localtime(&now);
    strftime(buf, sizeof(buf), "%a, %d %B %Y %X GMT", &tstruct);

    return buf;
}

void Response::get(string rootDir, string path, std::function<void (const string&)> sendHeader, std::function<void (int, size_t)> sendFile, bool flag) {
    path = UriDecode(path);
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
        int fd = open(absolutePath.c_str(), O_RDONLY);
        sendFile(fd, filesize);
//        close(fd);
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