#include <iostream>
#import "GameEngine.h"
#import <memory>
#import <fstream>
#include <sstream>

void kris::GameEngine::run() {
    std::string cmd;

    print_welcome();

    while (isRunning) {
        std::cout << environment->name() << ":> ";
        std::getline(std::cin, cmd);

        auto tokens = tokenize(cmd);
        if (tokens.size() < 1) continue;

        const std::string & command = tokens[0];

        if(router.find(command) != router.end()) {
            (this->*router[command])(tokens);
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

void kris::GameEngine::requestEnd(std::vector<std::string> const & d) {

    isRunning = false;
}

void kris::GameEngine::cmd_go(std::vector<std::string> const &words) {

    if (words.size() < 2) {
        std::cout << "Vars är du på väg, din lilla ärta?" << std::endl;
        return;
    }

    const std::string & str = words[1];
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

void kris::GameEngine::cmd_give(std::vector<std::string> const &aConst) {

}

void kris::GameEngine::cmd_steal(std::vector<std::string> const &aConst) {

}

void kris::GameEngine::cmd_use(std::vector<std::string> const &aConst) {

}

void kris::GameEngine::cmd_help(std::vector<std::string> const & aConst) {
    std::cout << "Kommandon:" << std::endl;
    for(std::map<std::string, CommandDealer>::iterator it = router.begin(); it != router.end(); it++) {
        std::cout << it->first << std::endl;
    }
}

void kris::GameEngine::cmd_describe(std::vector<std::string> const & d) {
    std::cout << environment->description() << std::endl;
}


void kris::GameEngine::init_router() {
    router["describe"] = &GameEngine::cmd_describe;
    router["quit"] = &GameEngine::requestEnd;
    router["help"] = &GameEngine::cmd_help;
    router["go"] = &GameEngine::cmd_go;
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

std::vector<std::string> kris::GameEngine::tokenize(std::string const &sentence) {
    std::istringstream iss(sentence);

    std::vector<std::string> tokens;
    copy(std::istream_iterator<std::string>(iss),
            std::istream_iterator<std::string>(),
            std::back_inserter(tokens));

    return tokens;

}
