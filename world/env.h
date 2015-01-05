#include "../util.h"

#ifndef ENV_GUARD
#define ENV_GUARD


namespace Kris {
    namespace Env {

        class Environment : Kris::Util::CommandHandler {
        public:
            virtual bool handleCommand(std::string &);
        };

        class OutdoorEnv : Environment {

        };


        class IndoorEnv : Environment {

        };

        class Hemicycle : IndoorEnv {

        };

        class OpinionCorridor : IndoorEnv {

        };


    }
}


#endif