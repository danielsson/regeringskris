#include <fstream>
#include "util.h"


using namespace kris::util;
void Util::print_file(std::string path) {
    std::string line;
    std::ifstream w_file(path);
    if (w_file.is_open()) {
        while (getline(w_file, line)) {
            std::cout << line << std::endl;
        }

        w_file.close();
    } else {
        std::cout << "File not found: " << path << std::endl;
    }
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