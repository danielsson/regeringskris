#include <iostream>
#include "env.h"

using namespace kris::env;

bool Environment::handleCommand(std::string & string) {
    return false;
}

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

void Environment::onEntry(kris::entities::Actor actor) {}

bool Environment::onDeparture(kris::entities::Actor actor) {
    return false;
}

void Environment::onPick(kris::entities::Physible physible) {

}

void Environment::onDrop(kris::entities::Physible physible) {

}

std::string GenericRoom::directions() {
    return _directions;
}

std::string GenericRoom::description() {
    return _description;
}
