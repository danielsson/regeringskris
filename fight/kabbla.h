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
            KabbalaAttack const &pick_at_random(std::vector<KabbalaAttack> const &attacks);
            void print_status();
            void gift();
            void do_dirty_laundry();
            void fight();
            std::pair<std::string, int> getNewspaper();
            std::string getComparison();
        public:

            KabblaMinigame(Environment *environment, Politician *contestant, Hero *hero)
                    : environment(environment), contestant(contestant), hero(hero) {
            }

            void kabbla();
        };
    }
}


#endif