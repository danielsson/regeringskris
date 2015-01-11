#import "world/entity.h"
#import "world/env.h"
#import <iostream>
#include <map>

#ifndef GAME_ENGINE_GUARD
#define GAME_ENGINE_GUARD


namespace kris {

    class GameEngine;

    typedef void (GameEngine::*CommandDealer)(std::string const&);

    class GameEngine {

    private:

        bool isRunning = true;
        env::Environment* environment;
        entities::Hero* hero;

        std::map<std::string, CommandDealer> router;

        void init_router();
        void print_welcome();

    public:
        GameEngine();
        void run();
        void requestEnd(std::string const &);


        void cmd_describe(std::string const&);
        void cmd_go(std::string const &);
        void cmd_give(std::string const &);
        void cmd_steal(std::string const &);
        void cmd_use(std::string const &);

        void cmd_help(std::string const &);


    };

}

#endif