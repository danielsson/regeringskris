#include <sstream>
#include "entity.h"

using namespace kris::entities;


bool Hero::handleCommand(std::string &str) {
    std::cout << str << std::endl;
    return false;
}

std::string Hero::type() {
    return "hero";
}


bool Actor::act() {
    return false;
}

Actor::Actor(std::string string) {

    _name = string;
}

std::string const &Actor::name() {
    return _name;
}

std::string const &Physible::name() const {
    return _name;
}

std::string Physible::description() const {
    return _desc;
}

std::string GenericItem::type() {
    return "generic";
}

Physible *Container::get_item(const std::string &name) {

    for (Physible *p : items) {
        if (p->name() == name) {
            return p;
        }
    }

    return 0;

}

int Physible::getWeight() const {
    return weight;
}

std::string Container::type() {
    return "container";
}

std::string Container::description() const {
    std::stringstream ss;

    ss << name() << "(" << _desc << ")" << std::endl;
    ss << items.size() << " items:" << std::endl;

    for (entities::Physible* p : items) {
        ss << p->name() << " " << p->description() << std::endl;
    }

    return ss.str();

}
