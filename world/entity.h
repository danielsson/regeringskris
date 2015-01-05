#include "../util.h"

#ifndef ENTITY_GUARD
#define ENTITY_GUARD


namespace Kris {
    namespace Entities {

        class Entity {

        public:
            virtual std::string type() = 0;
        };


        class Actor : Entity {
        protected:
            std::string _name;

        public:
            Actor(std::string name);
            virtual std::string const & name();
            virtual bool act();
        };


        class Politician : Actor {

        public:
            Politician(std::string str) : Actor(str) {}
        };


        class Hero : Actor, Kris::Util::CommandHandler {

        public:

            Hero(std::string name) : Actor(name) {};
            virtual std::string type();
            virtual bool handleCommand(std::string &);
        };


        /*class HousePlant : Actor {

        };*/


        /*
            ITEMS
         */


        class Physible : Entity {

        };

        class Container : Physible {

        };

        class GenericItem : Physible {

        };

        class Purse : Container {

        };

    }
}


#endif