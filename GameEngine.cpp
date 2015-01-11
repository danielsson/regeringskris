#include <iostream>
#import "GameEngine.h"
#import <memory>
#import <fstream>

void kris::GameEngine::run() {
    std::string cmd;

    print_welcome();

    while (isRunning) {
        std::cout << environment->name() << ":> ";
        std::getline(std::cin, cmd);

        if(router.find(cmd) != router.end()) {
            (this->*router[cmd])(cmd);
        } else {
            std::cout << "Ingen visste vad du menade, så det skickades på remiss till KU efter att någun funnit det kränkande." << std::endl;
        }
    }
}

void kris::GameEngine::print_welcome() {
    std::string line;
    std::ifstream w_file ("intro.txt");
    if (w_file.is_open()) {
        while (getline(w_file, line)) {
            std::cout << line << std::__1::endl;
        }

        w_file.close();
    } else {
        std::cout << "File not found: intro.txt" << std::__1::endl;
    }
}

void kris::GameEngine::requestEnd(std::string const & d) {

    isRunning = false;
}

void kris::GameEngine::cmd_go(std::string const &aConst) {

}

void kris::GameEngine::cmd_give(std::string const &aConst) {

}

void kris::GameEngine::cmd_steal(std::string const &aConst) {

}

void kris::GameEngine::cmd_use(std::string const &aConst) {

}

void kris::GameEngine::cmd_help(std::string const & aConst) {
    std::cout << "Available commands:" << std::endl;
    for(std::map<std::string, CommandDealer>::iterator it = router.begin(); it != router.end(); it++) {
        std::cout << it->first << std::endl;
    }
}

void kris::GameEngine::cmd_describe(std::string const &) {
    std::cout << environment->description() << std::endl;
}


void kris::GameEngine::init_router() {
    router["describe"] = &GameEngine::cmd_describe;
    router["quit"] = &GameEngine::requestEnd;
    router["help"] = &GameEngine::cmd_help;
}

kris::GameEngine::GameEngine() {

    init_router();

    hero = new entities::Hero("Löfven");

    entities::GenericItem* doll = new entities::GenericItem("Barbie", "A small doll");
    entities::GenericItem* apple = new entities::GenericItem("Apple", "An edible fruit");

    environment = new env::GenericRoom("Stadsminsterns kontor", "Ett kontor mycket passande för en lägre mellanchef på ett halvstatligt pappersbruk.");
    environment->getItems().add_item(doll);
    environment->getItems().add_item(apple);
}

