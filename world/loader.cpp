#include <iostream>
#include <fstream>
#include <assert.h>
#include <map>
#include "env.h"
#include "loader.h"
#include "../json/json.h"

using namespace kris;
using namespace kris::env;
using namespace kris::entities;

using json = nlohmann::json;

Environment *Loader::construct() {

    std::string world_file = get_file_contents(file_path);

    auto json = json::parse(world_file);

    std::map

    assert(json["@type"] == "World");





}


std::string Loader::get_file_contents(const std::string & filename)
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

Loader::Loader(std::string string) {
    file_path = string;
}
