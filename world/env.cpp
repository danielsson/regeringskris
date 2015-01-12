#include <iostream>
#include <sstream>
#include "env.h"

using namespace kris::env;

Environment*  Environment::neighbor(Direction& direction) {
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

std::string Environment::directions() {
    return "";
}

std::string Environment::description() {
    std::stringstream ss;

    ss << name() << std::endl;
    ss << _description << std::endl;

    ss << getItems().description() << std::endl;

    ss << getActors().size() << " people" << std::endl;

    for(auto it = getActors().begin(); it != getActors().end(); ++it) {
        ss << it->second->describe();
    }

    ss << std::endl << "Directions:" << std::endl;
    if(n_N) ss << "N " << n_N->name() << std::endl;
    if(n_E) ss << "E " << n_E->name() << std::endl;
    if(n_S) ss << "S " << n_S->name() << std::endl;
    if(n_W) ss << "W " << n_W->name() << std::endl;


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
