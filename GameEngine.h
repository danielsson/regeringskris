#import "world/entity.h"
#import "world/env.h"
#import <iostream>

#ifndef GAME_ENGINE_GUARD
#define GAME_ENGINE_GUARD


namespace Kris {


    class GameEngine {

    private:
        bool isRunning = true;
        Entities::Hero hero;
        Env::Environment environment;

    public:

        void run();
        void requestEnd();
    };

}

#endif