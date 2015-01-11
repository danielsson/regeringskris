#include <sstream>
#include "entity.h"

using namespace kris::entities;



std::string Hero::type() {
    return "hero";
}


bool Actor::act() {
    return false;
}

Actor::Actor(std::string string) {
    _name = string;
    _description = "Bakgrund okänd.";
}


Actor::Actor(std::string name, std::string desc, Physible* weakS) {
    this->_weakSpot = NULL;
    this->_name = name;
    this->_description = desc;
    this->_weakSpot = weakS;
}


std::string const &Actor::name() {
    return _name;
}

bool Actor::offered(Physible &item) {
    if(item.name() == _weakSpot->name()) {
        std::cout << "Det är ju inte som att du behöver mitt stöd till någonting. Men tack! Jag har alltid velat ha en sån här!" << std::endl;
        return true;
    }
    std::cout << "Vad är det där? Och vad ska jag med den till?" << std::endl;
    rant();
    return false;
}

void Actor::rant() {
    if(this->_name == "Göran Persson") {
        std::cout << "Jodu.. Så här långt hade det aldrig gått på min tid. Det var bättre förr." << std::endl;
    }

    if(this->_name == "Fredrik Reinfeldt") {
        std::cout << "Hjälp så Anders hade skrattat om han var här!" << std::endl;
    }
}




bool Politician::offered(Physible &item) {
    if(_givenConsent) {
        std::cout << "Men jag har ju redan sagt ja? Har inte du viktigare saker att göra?" << std::endl;
        return true;
    }
    if(item.name() == _weakSpot->name()) {
        giveConsent();
        return true;
    }
    std::cout << "Vad är det där? Och vad ska jag med den till?" << std::endl;
    rant();
    return false;
}

void Politician::giveConsent() {
    _givenConsent = true;
    std::cout << "Okej, du har mitt seal of approval." << std::endl;
}

void Politician::rant() {
    if(this->_name == "Annie Lööf") {
        std::cout << "Jag kommer aldrig, och då menar jag ALDRIG, stödja din regering!" << std::endl;
    }
    if(this->_name == "Åsa Romson") {
        std::cout << "Hur ska man kunna förvänta sig att min man läser alla detaljer på en färgburk?" << std::endl;
    }
    if(this->_name == "Anna Kinberg Batra") {
        std::cout << "Alliansen måste gemensamt föra en diskussion i samförstånd för att nå en överenskommelse." << std::endl;
    }
    if(this->_name == "Magdalena Andersson") {
        std::cout << "LADORNA ÄR TOMMA. Varför tror ingen på mig?" << std::endl;
    }
}

std::string const &Physible::name() const {
    return _name;
}

std::string Physible::description() const {
    return _desc;
}

std::string GenericItem::type() {
    return "GenericItem";
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
    return "Container";
}

std::string Container::description() const {
    std::stringstream ss;

    ss << name() << "(" << _desc << ")" << std::endl;
    ss << items.size() << " saker:" << std::endl;

    for (entities::Physible* p : items) {
        ss << p->name() << " – " << p->description() << std::endl;
    }

    return ss.str();

}

bool Physible::use() {
    return false;
}

bool Politician::consent() {
    return _givenConsent;
}

std::string Entity::type() {
    return "Entity";
}
