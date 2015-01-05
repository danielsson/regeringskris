#include "entity.h"

using namespace Kris::Entities;



bool Hero::handleCommand(std::string & str) {
    std::cout << str << std::endl;
    return false;
}