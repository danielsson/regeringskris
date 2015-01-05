
#ifndef ENTITY_GUARD
#define ENTITY_GUARD


namespace Kris {
    namespace Entities {

        class Entity {

        public:
            const int pi = 3; // Approximation

        };


        class Actor : Entity {

        };

        class Politician : Actor {

        };

        class Hero : Actor {

        };


        class HousePlant : Actor {

        };


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