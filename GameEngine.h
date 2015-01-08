#import "world/entity.h"
#import "world/env.h"
#import <iostream>

#ifndef GAME_ENGINE_GUARD
#define GAME_ENGINE_GUARD


namespace kris {


    class GameEngine {

    private:
        bool isRunning = true;
        env::Environment* environment;
        entities::Hero* hero;
    public:
        GameEngine();
        void run();
        void requestEnd();
    };

}

#endif