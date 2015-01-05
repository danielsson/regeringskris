#include <iostream>
#import "GameEngine.h"


void Kris::GameEngine::run() {

    while (isRunning) {

        std::string cmd;
        std::getline(std::cin, cmd);

        if(cmd.size() < 2) isRunning = false;

        if (!environment.handleCommand(cmd)) {
            if(!hero.handleCommand(cmd)) {
                std::cout << "Ingen visste vad som behövde göras" << std::endl;

            }
        }

    }



}

void Kris::GameEngine::requestEnd() {

    isRunning = false;
}
