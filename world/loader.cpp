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


void read_item(json &obj, Environment* env) {

}


void read_environment(json &obj, std::map<std::string, Environment *> &environments) {
    std::string id = obj["@id"];

    Environment* retval = 0;

    std::string name = obj["name"];
    std::string description = obj["description"];

    if (obj["@type"] == GenericRoom::type()) {
        retval = new GenericRoom(name, description);
    }

    if (obj.find("items") != obj.end()) {
        for (json item : obj["items"]) {
            read_item(item, retval);
        }
    }

    if (retval)
        environments[id] = retval;
}




void read_environments(json &obj, std::map<std::string, Environment *> &environments) {
    for(json & room : obj) {
        read_environment(room, environments);
    }
}

void read_neighbors(json &obj, std::map<std::string, Environment *> &environments) {

    for(json::iterator it = obj.begin(); it != obj.end(); ++it) {

        Environment* from = environments[it.key()];

        for(json::iterator jt = it.value().begin(); jt != it.value().end(); ++jt) {

            Environment* to = environments[jt.value().get<std::string>()];

            Direction dir = Environment::fromString(jt.key());

            from->set_neighbor(dir, to);

        }

    }
}


Environment *Loader::construct() {

    std::string world_file = get_file_contents(file_path);
    std::map<std::string, Environment*> environments;

    auto obj = json::parse(world_file);


    assert(obj["@type"] == "World");

    std::string start_location = obj["start"];

    read_environments(obj["rooms"], environments);

    read_neighbors(obj["neighbors"], environments);

    return environments[start_location];

}




#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wsign-conversion"
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
#pragma clang diagnostic pop

Loader::Loader(std::string string) {
    file_path = string;
}
