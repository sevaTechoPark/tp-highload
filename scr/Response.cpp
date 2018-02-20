//
// Created by seva on 18.02.18.
//

#include "Response.h"
//#include <fstream>
#include "boost/filesystem/operations.hpp"
#include "boost/filesystem/path.hpp"
#include "boost/progress.hpp"


namespace fs = boost::filesystem;


void Response::sendFile(string rootDir, string path, std::function<void (const string&)> sendHeader, std::function<void (int)> sendFile) {

    fs::path p(rootDir + path);
    if (boost::filesystem::is_regular_file(p)) {

        int fd = open(p.string().c_str(), O_RDONLY);
//        std::cout <<  p.string() << " " << p.compare(rootDir) << std::endl;
        sendFile(fd);
    } else {
        sendHeader(notFound);
    }
//    std::ifstream in(p);
//
//    while (size_t count = static_cast<size_t>(in.readsome(buffer, bufferSize))) {
//        sendHeader(std::string(buffer, count));
//    }
}