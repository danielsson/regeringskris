#include <vector>
#include "../util.h"

#ifndef ENTITY_GUARD
#define ENTITY_GUARD


namespace kris {
    namespace entities {
        class Physible;

        class Entity {

        public:
            static std::string type();
        };


        class Actor : Entity {
        protected:
            std::string _name;
            std::string _description;
            Physible* _weakSpot;

        public:
            Actor(std::string name, std::string desc, Physible* weakS);

            Actor(std::string name);
            virtual std::string const & name();
            virtual bool act();
            virtual bool offered(Physible &);
            virtual void rant();
        };


        class Politician : Actor {
        protected:
            bool _givenConsent;

        public:
            virtual bool offered(Physible &);
            Politician(std::string str) : Actor(str) {
                _givenConsent = false;
            }
            virtual void giveConsent();
            virtual void rant();
            bool consent();
        };


        class Hero : Actor {

        public:

            Hero(std::string name) : Actor(name) {};
            static std::string type();

        };


        /*class HousePlant : Actor {

        };*/


        /*
            ITEMS
         */


        class Physible : protected Entity {

        protected:
            std::string _name;
            std::string _desc;
            int weight = 1;

        public:
            virtual std::string const &name() const;
            virtual std::string description() const;
            virtual int getWeight() const;
            virtual bool use();
        };

        class Container : Physible {

        protected:
            std::vector<entities::Physible*> items;

        public:
            void add_item(entities::Physible* item) {
                items.push_back(item);
            }

            entities::Physible* get_item(const std::string& name);
            virtual std::string type();

            virtual std::string description() const;

        };

        class GenericItem : public Physible {
        public:

            GenericItem(std::string _name, std::string _desc, int weight) {
                this->_desc = _desc;
                this->weight = weight;
                this->_name = _name;
            }

            static std::string type();

        };

        class Purse : Container {

        };

    }
}


#endif