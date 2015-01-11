#include <vector>
#include "../util.h"

#ifndef ENTITY_GUARD
#define ENTITY_GUARD


namespace kris {
    namespace entities {


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


        class Hero : Actor, kris::util::CommandHandler {

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


        class Physible : protected Entity {

        protected:
            std::string _name;
            std::string _desc;
            int weight = 1;

        public:
            virtual std::string const &name() const;
            virtual std::string description() const;
            virtual int getWeight() const;
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

            GenericItem(std::string _name, std::string _desc) {
                this->_desc = _desc;
                this->_name = _name;
            }
            virtual std::string type();

        };

        class Purse : Container {

        };

    }
}


#endif