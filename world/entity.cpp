
#include "entity.h"

using namespace Kris::Entities;


bool Hero::handleCommand(std::string & str) {
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

