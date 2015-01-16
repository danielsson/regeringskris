#import "world/entity.h"
#import "world/env.h"
#include "world/loader.h"
#import <iostream>
#include <map>

#ifndef GAME_ENGINE_GUARD
#define GAME_ENGINE_GUARD


namespace kris {

    class GameEngine;

    typedef void (GameEngine::*CommandDealer)(std::vector<std::string> const &);

    class GameEngine {

    private:

        bool isRunning = true;

        Loader loader;

        env::Environment* environment;
        entities::Hero* hero;

        std::map<std::string, CommandDealer> router;

        void init_router();

        std::vector<std::string> tokenize(const std::string &);

    public:
        GameEngine();
        void run();
        void requestEnd(std::vector<std::string> const &);

        void cmd_describe(std::vector<std::string> const &);
        void cmd_go(std::vector<std::string> const &);
        void cmd_give(std::vector<std::string> const &);
        void cmd_take(std::vector<std::string> const &);
        void cmd_steal(std::vector<std::string> const &);
        void cmd_use(std::vector<std::string> const &);

        void cmd_help(std::vector<std::string> const &);
        void cmd_inventory(std::vector<std::string> const &);

        void cmd_kabbla(std::vector<std::string> const &);

        void cmd_tally(std::vector<std::string> const &);



    };

}

#endif