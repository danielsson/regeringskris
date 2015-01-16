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

void Loader::read_item(json &obj, Environment* env) {

    std::string id = obj["@id"];
    std::string name = obj["name"];
    std::string description = getDefault(obj, "description", "");
    int weight = getDefault(obj, "weight", 1);

    if (obj["@type"] == "GenericItem") {
        GenericItem *item = new GenericItem(name, description, weight);
        add_managed_pointer(item);
        item->setId(id);

        if (obj.find("moveable") != obj.end()) {
            item->setMoveable(obj["moveable"]);
        }

        env->getItems().add_item(item);
    } else {
        std::cerr << "Unknown item @type " << obj["@type"] << std::endl;
    }
}

std::vector<KabbalaAttack> Loader::read_attacks(json & obj, Politician * pol) {
    std::vector<KabbalaAttack> vec;


    for (json & o : obj) {
        int p = o["probability"];
        int r = o["resistance"];
        int s = o["sjalvaktning"];
        std::string m = o["message"];
        KabbalaAttack k(p, r, s, m);
        vec.push_back(k);
    }

    return vec;
}

void Loader::read_actor(json & obj, Environment * environment) {

    std::string id = obj["@id"];
    std::string name = obj["name"];
    std::string description = getDefault(obj, "description", "");

    if (obj["@type"] == "Politician") {
        std::string str = obj["allegiance"];
        Party p = Politician::partyMapping[str];
        Politician *pol = new Politician(name, description, p);
        add_managed_pointer(pol);
        pol->setId(id);

        if (obj.find("image") != obj.end()) {
            std::string img = obj["image"];
            pol->setImageName(img);
        }

        if (obj.find("resistance") != obj.end()) {
            int pt = obj["resistance"];
            pol->setResistancePoints(pt);
        }

        if (obj.find("kabbala") != obj.end()) {
            std::vector<KabbalaAttack> attacks = read_attacks(obj["kabbala"]["attacks"], pol);
            pol->setAttacks(attacks);
        }

        environment->getActors()[name] = pol;


    } else if (obj["@type"] == "Actor") {
        Actor* a = new Actor(name, description, nullptr);
        add_managed_pointer(a);
        a->setId(id);
        environment->getActors()[name] = a;

    } else {
        std::cerr << "Unknown actor @type " << obj["@type"] << std::endl;
    }

}

void Loader::read_environment(json &obj, std::map<std::string, Environment *> &environments) {
    std::string id = obj["@id"];

    Environment* retval = 0;

    std::string name = obj["name"];
    std::string description = obj["description"];

    if (obj["@type"] == GenericRoom::type()) {
        retval = new GenericRoom(name, description);
        add_managed_pointer(retval);
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

    if (retval) {
        environments[id] = retval;
    }
}




void Loader::read_environments(json &obj, std::map<std::string, Environment *> &environments) {
    for(json & room : obj) {
        read_environment(room, environments);
    }
}

void Loader::read_neighbors(json &obj, std::map<std::string, Environment *> &environments) {

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

void Loader::add_managed_pointer(Actor *ptr) {
    actors.push_back(ptr);
}

void Loader::add_managed_pointer(Physible *ptr) {
    physibles.push_back(ptr);
}

void Loader::add_managed_pointer(Environment *ptr) {
    envs.push_back(ptr);
}

Loader::~Loader() {

    for(Actor * a : actors) {
        delete a;
    }

    for(Physible * p : physibles) {
        delete p;
    }

    for(Environment * e : envs) {
        delete e;
    }

}
