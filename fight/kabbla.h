#ifndef KABBLA_GUARD
#define KABBLA_GUARD

#include <vector>
#include <map>
#include "../world/entity.h"
#include "../world/env.h"

namespace kris {
    namespace kabbala {

        using namespace kris::env;
        using namespace kris::entities;

        class KabblaMinigame {
        protected:
            Environment * environment;
            Politician * contestant;
            Hero * hero;

            bool isPlaying = true;
            int sjalvaktning = 100;

            void contestant_move();
        public:

            KabblaMinigame(Environment *environment, Politician *contestant, Hero *hero)
                    : environment(environment), contestant(contestant), hero(hero) {
            }


            void kabbla();

        };
    }
}


#endif