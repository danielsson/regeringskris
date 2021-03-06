#include <iostream>
#include <sstream>
#include "env.h"
#include "entity.h"

using namespace kris::env;
using namespace kris::entities;

Environment *  Environment::neighbor(Direction& direction) const {
    switch (direction) {
        case N:
            return n_N;
        case E:
            return n_E;
        case S:
            return n_S;
        case W:
        default:
            return n_W;
    }
}

void Environment::onEntry(kris::entities::Actor* actor) {}

bool Environment::onDeparture(kris::entities::Actor* actor) {
    return false;
}

void Environment::onPick(kris::entities::Physible* physible) {

}

void Environment::onDrop(kris::entities::Physible* physible) {

}

std::string Environment::directions() const{
    return "";
}

std::string Environment::description() const {
    std::stringstream ss;

    ss << name() << std::endl;
    ss << "\t" << _description << std::endl;

    ss << getItems().description() << std::endl;

    ss << getActors().size() << " people" << std::endl;

    for(auto it = getActors().begin(); it != getActors().end(); ++it) {
        ss << "\t" << it->second->describe();
    }

    ss << std::endl << "Riktningar:" << std::endl;
    if(n_N) ss << "\t" << "N " << n_N->name() << std::endl;
    if(n_E) ss << "\t" << "E " << n_E->name() << std::endl;
    if(n_S) ss << "\t" << "S " << n_S->name() << std::endl;
    if(n_W) ss << "\t" << "W " << n_W->name() << std::endl;


    return ss.str();
}

std::string Environment::type() {
    return "Environment";
}


Direction Environment::fromString(std::string str) {
    Direction direction;

    if (str == "n" || str == "N") {
        direction = Direction::N;
    } else if (str == "e" || str == "E") {
        direction = Direction::E;
    } else if (str == "s" || str == "S") {
        direction = Direction::S;
    } else {
        direction = Direction::W;
    }

    return direction;
}

void Environment::set_neighbor(Direction d, Environment *environment) {
    switch (d) {
        case N:
            n_N = environment;
            break;
        case S:
            n_S = environment;
            break;
        case W:
            n_W = environment;
            break;
        case E:
            n_E = environment;
    }
}

Container& Environment::getItems() {
    return items;
}

Container const& Environment::getItems() const {
    return items;
}


std::map<std::string, Actor*> & Environment::getActors() {
    return actors;
}

std::map<std::string, Actor*> const &Environment::getActors() const {
    return actors;
}


GenericRoom::GenericRoom(std::string name, std::string _description) {
this->_name = name;
this->_directions = _directions;
this->_description = _description;
}


std::string GenericRoom::name() const{
    return _name;
}

std::string GenericRoom::type() {
    return "GenericRoom";
}
