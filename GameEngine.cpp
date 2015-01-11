#include <iostream>
#import "GameEngine.h"
#import <memory>


void kris::GameEngine::run() {

    while (isRunning) {

        std::string cmd;
        std::getline(std::cin, cmd);

        if(cmd.size() < 2) {
            requestEnd();
            continue;
        }

        if (cmd == "describe") {
            std::cout << environment->description() << std::endl;
        }
    }
}

void kris::GameEngine::requestEnd() {

    isRunning = false;
}

kris::GameEngine::GameEngine() {

    hero = new entities::Hero("Merlin");

    entities::GenericItem* doll = new entities::GenericItem("Barbie", "A small doll");
    entities::GenericItem* apple = new entities::GenericItem("Apple", "An edible fruit");

    environment = new env::GenericRoom("Stadsminsterns kontor", "Ett kontor mycket passande för en lägre mellanchef på ett halvstatligt pappersbruk.");
    environment->getItems().add_item(doll);
    environment->getItems().add_item(apple);
}
