#include <iostream>

#ifndef UTIL_GUARD
#define UTIL_GUARD

namespace kris {
    namespace util {

        class Util {
        public:
            static std::string get_file_contents(const std::string & filename);
            static void print_file(std::string path);
        };
    }
}

#endif