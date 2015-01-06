#include <iostream>
#import "GameEngine.h"
#import <memory>


void kris::GameEngine::run() {

    while (isRunning) {

        std::string cmd;
        std::getline(std::cin, cmd);

        if(cmd.size() < 2) break;

        if (!environment->handleCommand(cmd)) {
            if(!hero.handleCommand(cmd)) {
                std::cout << "Ingen visste vad som behövde göras" << std::endl;
            }
        }

    }



}

void kris::GameEngine::requestEnd() {

    isRunning = false;
}

kris::GameEngine::GameEngine() : hero("merlin") {

    entities::GenericItem doll("Barbie", "A small doll");
    entities::GenericItem apple("Apple", "An edible fruit");

    environment = std::make_shared(env::GenericRoom("lololdirect", "Desc"));

    environment->addItem(doll);
    environment->addItem(apple);
}
