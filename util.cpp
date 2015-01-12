#include <fstream>
#include "util.h"


using namespace kris::util;

std::string CommandHandler::readWord(std::string & str) {
    return "";
}

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wsign-conversion"
std::string Util::get_file_contents(const std::string & filename)
{
    std::ifstream in(filename, std::ios::in | std::ios::binary);
    if (in)
    {
        std::string contents;
        in.seekg(0, std::ios::end);
        contents.resize(in.tellg());
        in.seekg(0, std::ios::beg);
        in.read(&contents[0], contents.size());
        in.close();
        return(contents);
    }
    throw(errno);
}
#pragma clang diagnostic pop