#include <iostream>
#include <fstream>
#include <assert.h>
#include <map>
#include "env.h"
#include "loader.h"
#include "../json/json.h"
#include "../util.h"

using namespace kris;
using namespace kris::env;
using namespace kris::entities;
using namespace kris::util;

using json = nlohmann::json;


std::string getDefault(json &obj, std::string key, std::string _default) {

    if(obj.find(key) != obj.end()) {
        return obj[key];
    } else {
        return _default;
    }
}
int getDefault(json &obj, std::string key, int _default) {

    if(obj.find(key) != obj.end()) {
        return obj[key];
    } else {
        return _default;
    }
}

void read_item(json &obj, Environment* env) {

    std::string id = obj["@id"];
    std::string name = obj["name"];
    std::string description = getDefault(obj, "description", "");
    int weight = getDefault(obj, "weight", 1);

    if (obj["@type"] == GenericItem::type()) {
        GenericItem *item = new GenericItem(name, description, weight);

        if (obj.find("moveable") != obj.end()) {
            item->setMoveable(obj["moveable"]);
        }

        env->getItems().add_item(item);
    } else {
        std::cerr << "Unknown item @type " << obj["@type"] << std::endl;
    }
}

void read_actor(json & obj, Environment * environment) {

    std::string id = obj["@id"];
    std::string name = obj["name"];
    std::string description = getDefault(obj, "description", "");

    if (obj["@type"] == "Politician") {
        std::string str = obj["allegiance"];
        Party p = Politician::partyMapping[str];
        Politician* pol = new Politician(name, description, p);

        if (obj.find("image") != obj.end()) {
            std::string img = obj["image"];
            pol->setImageName(img);
        }

        if (obj.find("resistance") != obj.end()) {
            int pt = obj["resistance"];
            pol->setResistancePoints(pt);
        }

        environment->getActors()[name] = pol;

    } else {
        std::cerr << "Unknown actor @type " << obj["@type"] << std::endl;
    }

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

    if (obj.find("actors") != obj.end()) {
        for (json actor : obj["actors"]) {
            read_actor(actor, retval);
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

    std::string world_file = Util::get_file_contents(file_path);
    std::map<std::string, Environment*> environments;

    auto obj = json::parse(world_file);


    assert(obj["@type"] == "World");

    const std::string start_location = obj["start"];

    read_environments(obj["env"], environments);

    read_neighbors(obj["neighbors"], environments);

    return environments[start_location];

}






Loader::Loader(std::string string) {
    file_path = string;
}
