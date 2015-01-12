#include <iostream>
#import "GameEngine.h"
#import <memory>
#import <fstream>
#include <sstream>

using namespace kris;

void GameEngine::run() {
    std::string cmd;

    print_welcome();

    std::srand((unsigned int) std::time(0));

    while (isRunning) {
        std::cout << environment->name() << ":> ";
        std::getline(std::cin, cmd);

        auto tokens = tokenize(cmd);
        if (tokens.size() < 1) continue;

        const std::string &command = tokens[0];

        if (router.find(command) != router.end()) {
            (this->*router[command])(tokens);
        } else {
            std::cout << "Ingen visste vad du menade, men någon fann det kränkande och anmälde det till KU" << std::endl;
        }
    }
}

void GameEngine::print_welcome() {
    std::string line;
    std::ifstream w_file("intro.txt");
    if (w_file.is_open()) {
        while (getline(w_file, line)) {
            std::cout << line << std::endl;
        }

        w_file.close();
    } else {
        std::cout << "File not found: intro.txt" << std::endl;
    }
}

void GameEngine::requestEnd(std::vector<std::string> const &d) {

    isRunning = false;
}

void GameEngine::cmd_go(std::vector<std::string> const &words) {

    if (words.size() < 2) {
        std::cout << "Vars är du på väg?" << std::endl;
        return;
    }

    const std::string &str = words[1];
    env::Direction direction;

    if (str == "n") {
        direction = env::Direction::N;
    } else if (str == "e") {
        direction = env::Direction::E;
    } else if (str == "s") {
        direction = env::Direction::S;
    } else if (str == "w") {
        direction = env::Direction::W;
    } else {
        std::cout << "Okänd riktning! Vill du åka hem?" << std::endl;
        return;
    }

    auto e = environment->neighbor(direction);

    if (e) {
        environment = e;
    } else {
        std::cout << "Finns inget att se åt det hållet." << std::endl;
    }

}

void GameEngine::cmd_give(std::vector<std::string> const &aConst) {
    if (aConst.size() < 3) return;

    const std::string &thing = aConst[1];
    const std::string &actor = aConst[2];

    Physible *p = hero->getItems().get_item(thing);

    if (!p) {
        std::cout << "Du har ingen " << thing << std::endl;
        return;
    }

    if (environment->getActors().find(actor) != environment->getActors().end()) {
        environment->getActors()[actor]->offered(p);
    } else {
        std::cout << "Ingen jävel som heter så här." << std::endl;
    }
}

void GameEngine::cmd_take(std::vector<std::string> const &cmd) {
    if (cmd.size() < 2) return;

    const std::string &thing = cmd[1];

    Container::TransferError err = environment->getItems().transfer_to(thing, hero->getItems());

    switch (err) {
        case Container::TransferError::NotFound:
            std::cout << "Ej funnen" << std::endl;
            break;
        case Container::TransferError::Immovable:
            std::cout << "Du försökte flytta " << thing << " men du var inte stark nog." << std::endl;
            break;
        case Container::TransferError::OK:
            std::cout << "Tog " << thing << std::endl;
            break;
        default:
            break;
    }

}


void GameEngine::cmd_steal(std::vector<std::string> const &aConst) {

}

void GameEngine::cmd_inventory(std::vector<std::string> const &vector) {

    std::cout << hero->getItems().description() << std::endl;
}


void GameEngine::cmd_use(std::vector<std::string> const &cmd) {
    if (cmd.size() < 2) return;

    Physible *p = hero->getItems().get_item(cmd[1]);
    if (p) {
        p->use();
        return;
    }

    p = environment->getItems().get_item(cmd[1]);
    if (p) {
        p->use();
        return;
    }

    if (environment->getActors().find(cmd[1]) != environment->getActors().end()) {
        environment->getActors()[cmd[1]]->act();
    } else {
        std::cout << "Vet inte vad " << cmd[1] << " är \n";
    }

}

void GameEngine::cmd_help(std::vector<std::string> const &aConst) {
    std::cout << "Kommandon:" << std::endl;
    for (std::map<std::string, CommandDealer>::iterator it = router.begin(); it != router.end(); it++) {
        std::cout << it->first << std::endl;
    }
}

void GameEngine::cmd_describe(std::vector<std::string> const &d) {
    std::cout << environment->description() << std::endl;
}

void GameEngine::cmd_kabbla(std::vector<std::string> const &cmd) {
    if (cmd.size() < 2) return;

    const std::string &name = cmd[1];

    if (environment->getActors().find(name) != environment->getActors().end()) {
        environment->getActors()[name]->kabbla(hero);
    } else {
        std::cout << "Vet inte vem " << name << " är \n";
    }
}



void GameEngine::init_router() {
    router["beskriv"] = &GameEngine::cmd_describe;
    router["avgå"] = &GameEngine::requestEnd;
    router["hjälp"] = &GameEngine::cmd_help;
    router["gå"] = &GameEngine::cmd_go;
    router["bruka"] = &GameEngine::cmd_use;
    router["inventarier"] = &GameEngine::cmd_inventory;
    router["ge"] = &GameEngine::cmd_give;
    router["ta"] = &GameEngine::cmd_take;
    router["käbbla"] = &GameEngine::cmd_kabbla;
}

GameEngine::GameEngine() : loader("die_welt.json") {
    hero = new entities::Hero("Löfven");

    environment = loader.construct();

    init_router();

}

std::vector<std::string> GameEngine::tokenize(std::string const &sentence) {
    std::istringstream iss(sentence);
    std::vector<std::string> tokens;

    copy(std::istream_iterator<std::string>(iss),
            std::istream_iterator<std::string>(),
            std::back_inserter(tokens));

    return tokens;

}

