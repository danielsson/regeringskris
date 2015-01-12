#include <iostream>
#include <fstream>
#include "../json/json.h"
#include "env.h"
#include "entity.h"

#ifndef LOADER_GUARD
#define LOADER_GUARD

using namespace kris::env;
using namespace kris::entities;

namespace kris {

    class Loader {

    protected:
        std::string file_path;

    public:
        Loader(std::string);
        Environment* construct();


    };


}



#endif