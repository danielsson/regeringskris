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

std::string const &Physible::description() const {
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
