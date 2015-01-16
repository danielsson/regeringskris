#include <sstream>
#include "entity.h"
#include "../fight/kabbla.h"
#include "../GameEngine.h"

using namespace kris::entities;
using namespace kris::util;


std::map<std::string, Party> Politician::partyMapping{
        {"VPK", VPK},
        {"S", S},
        {"MP", MP},
        {"C", C},
        {"KD", KD},
        {"FP", FP},
        {"M", M},
        {"SD", SD},
        {"FI", FI},
        {"P", P}
};

std::map<Party, std::string> Politician::partyMappingReversed{
        {VPK,"VPK"},
        {S, "S"},
        {MP, "MP"},
        {C, "C"},
        {KD, "KD"},
        {FP, "FP"},
        {M, "M"},
        {SD, "SD"},
        {FI, "FI"},
        {P, "P"}
};


bool Actor::act() {
    this->rant();
    return false;
}

Actor::Actor(std::string string) {
    _name = string;
    _description = "Bakgrund okänd.";
}


Actor::Actor(std::string name, std::string desc, Physible *weakS) {
    this->_weakSpot = NULL;
    this->_name = name;
    this->_description = desc;
    this->_weakSpot = weakS;
}


std::string const &Actor::name() {
    return _name;
}

bool Actor::offered(Physible *item) {
    if (item->name() == _weakSpot->name()) {
        std::cout << "Det är ju inte som att du behöver mitt stöd till någonting. Men tack! Jag har alltid velat ha en sån här!" << std::endl;
        return true;
    }
    std::cout << "Vad är det där? Och vad ska jag med den till?" << std::endl;
    rant();
    return false;
}

void Actor::rant() {
    if (this->_name == "Göran Persson") {
        std::cout << "Jodu.. Så här långt hade det aldrig gått på min tid. Det var bättre förr." << std::endl;
    }

    if (this->_name == "Fredrik Reinfeldt") {
        std::cout << "Hjälp så Anders hade skrattat om han var här!" << std::endl;
    }
}


bool Politician::offered(Physible &item) {
    if (_givenConsent) {
        std::cout << "Men jag har ju redan sagt ja? Har inte du viktigare saker att göra?" << std::endl;
        return true;
    }
    if (item.name() == _weakSpot->name()) {
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
    if (this->_name == "Annie") {
        std::cout << "Jag kommer aldrig, och då menar jag ALDRIG, stödja din regering!" << std::endl;
    }
    else if (this->_name == "Åsa Romson") {
        std::cout << "Hur ska man kunna förvänta sig att min man läser alla detaljer på en färgburk?" << std::endl;
    }
    else if (this->_name == "Anna Kinberg Batra") {
        std::cout << "Alliansen måste gemensamt föra en diskussion i samförstånd för att nå en överenskommelse." << std::endl;
    }
    else if (this->_name == "Magdalena Andersson") {
        std::cout << "LADORNA *ÄR* TOMMA. Varför tror ingen på mig?" << std::endl;
    } else {
        std::cout << "Vem är det som är kapten på den här skutan egentligen?" << std::endl;
    }
}

std::string const &Physible::name() const {
    return _name;
}

std::string Physible::description() const {
    return _desc;
}

Physible *Container::get_item(const std::string &name) {
    for (Physible *p : items) {
        if(iequals(p->name(), name)) {
            return p;
        }
    }

    return 0;

}

bool Physible::iequals(const std::string& a, const std::string& b)
{
    unsigned long sz = a.size();
    if (b.size() != sz)
        return false;
    for (unsigned int i = 0; i < sz; ++i)
        if (tolower(a[i]) != tolower(b[i]))
            return false;
    return true;
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
    ss << items.size() << " pryl(ar):" << std::endl;

    for (entities::Physible *p : items) {
        ss << p->name() << " – " << p->description() << " (" << weight << " kg)" << std::endl;
    }

    return ss.str();

}

bool Physible::use() {

    std::cout << "Kan inte använda " << name() << std::endl;
    return false;
}

bool Politician::consent() {
    return _givenConsent;
}

std::string Actor::describe() {
    std::stringstream ss;

    ss << name() << " - " << _description << std::endl;

    return ss.str();
}

std::string Politician::describe() {
    std::stringstream ss;

    ss << name() << "(" << partyMappingReversed[affiliation] << ") - " << _description << std::endl;

    return ss.str();
}

Container::TransferError Container::transfer_to(const std::string &name, Container &other) {

    Physible* p = get_item(name);
    if (!p) {
        return NotFound;
    }

    if (!p->isMoveable())
        return Immovable;

    items.erase(std::remove(items.begin(), items.end(), p), items.end());
    other.add_item(p);

    return OK;
}

void Actor::kabbla(Hero *hero) {
    std::cout << "Jag vill inte bråka!\n";
}

void Politician::kabbla(Hero *hero) {
    kabbala::KabblaMinigame kabblaMinigame(nullptr, this, hero);
    kabblaMinigame.kabbla();
}

bool Oracle::act() {

    std::cout << "Det är farligt att gå ensam, ta denna:\n";

    Physible * p = new HolyArtifact("Internationalen", "I orginalversion, men Göran Greiders autograf på omslaget.");
    return true;
}

bool HolyArtifact::use() {

    return true;

}

KabbalaAttack::KabbalaAttack(int probability, int resistance_modifier, int sjalvaktning_modifier, std::string message)
        : probability(probability),
          resistance_modifier(resistance_modifier),
          sjalvaktning_modifier(sjalvaktning_modifier),
          message(message) {
}

std::string const &Entity::getId() const {
    return id;
}

void Entity::setId(std::string &id) {
    Entity::id = id;
}

bool Physible::isMoveable() const {
    return moveable;
}

void Physible::setMoveable(bool moveable) {
    Physible::moveable = moveable;
}

void Container::add_item(Physible* item) {
    items.push_back(item);
}

GenericItem::GenericItem(std::string _name, std::string _desc, int _weight) {
this->_desc = _desc;
this->weight = _weight;
this->_name = _name;
}

HolyArtifact::HolyArtifact(std::string _name, std::string _desc) {
    this->_desc = _desc;
    this->_name = _name;
}

std::string Actor::type() {
    return "actor";
}

std::string const &Actor::getImageName() const {
    return image_name;
}

void Actor::setImageName(std::string &image_name) {
    Actor::image_name = image_name;
}

Container &Actor::getItems() {
    return items;
}

Politician::Politician(std::string str, std::string _desc, Party affiliation) : Actor(str) {
        _givenConsent = false;
        _description = _desc;
        this->affiliation = affiliation;
}

Party Politician::getAffiliation() {
    return affiliation;
}

std::string Politician::type() {
    return "politician";
}

/**
* How resistant are this politician against your politics?
*/
int Politician::getResistancePoints() const {
    return resistancePoints;
}

void Politician::setResistancePoints(int resistancePoints) {
    Politician::resistancePoints = resistancePoints;
}


std::vector<KabbalaAttack> const &Politician::getAttacks() const {
    return attacks;
}

void Politician::setAttacks(std::vector<KabbalaAttack> &attacks) {
    Politician::attacks = attacks;
}

Oracle::Oracle(std::string &name, std::string &desc, Physible *weakS) : Actor(name, desc, weakS) {
}

Hero::Hero(std::string name) : Actor(name) {};