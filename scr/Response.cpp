//
// Created by seva on 18.02.18.
//

#include "Response.h"
//#include <fstream>
#include "boost/filesystem/operations.hpp"
#include "boost/filesystem/path.hpp"
#include "boost/progress.hpp"
#include "boost/algorithm/string.hpp"

namespace fs = boost::filesystem;


void Response::sendFile(string rootDir, string path, std::function<void (const string&)> sendHeader, std::function<void (int)> sendFile) {

    fs::path relativePath(rootDir + path);

    if (is_directory(relativePath)) { // Directory index file name index.html
        relativePath /= "index.html";
    }

    boost::system::error_code ec;
    fs::path absolutePath = canonical(relativePath, rootDir, ec);
    if (ec) { // this file/dir does not exist
        sendHeader(notFound);
        return;
    }

    if(!checkRootDir(absolutePath.string(), rootDir)) {
        sendHeader(notFound); // this file over the root_path
        return;
    }

    boost::uintmax_t filesize = file_size(relativePath, ec);
    
    int fd = open(relativePath.string().c_str(), O_RDONLY);
    sendFile(fd);
}

bool Response::checkRootDir(string rootDir, string path) {
    return boost::algorithm::contains(rootDir, path);
}
