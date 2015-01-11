#include <vector>
#include <map>
#include "../util.h"

#ifndef ENTITY_GUARD
#define ENTITY_GUARD


namespace kris {
    namespace entities {

        enum Party {
            VPK, S, MP, C, KD, FP, M, SD, FI, P
        };



        class Physible;

        class Entity {

        public:
            static std::string type();
            static std::map<std::string, Party> partyMapping;

            static std::map<Party, std::string> partyMappingReversed;
        };


        class Actor : public Entity {
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

            virtual std::string describe();
        };


        class Politician : public Actor {
        protected:
            bool _givenConsent;
            Party affiliation;

        public:
            virtual bool offered(Physible &);
            Politician(std::string str, std::string _desc, Party affiliation) : Actor(str) {
                _givenConsent = false;
                _description = _desc;
                this->affiliation = affiliation;
            }
            virtual void giveConsent();
            virtual void rant();
            bool consent();
            virtual std::string describe();

            Party getAffiliation() {
                return affiliation;
            }
        };


        class Hero : Actor {

        public:

            Hero(std::string name) : Actor(name) {};
            static std::string type();

        };



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

            GenericItem(std::string _name, std::string _desc, int _weight) {
                this->_desc = _desc;
                this->weight = _weight;
                this->_name = _name;
            }

            static std::string type();

        };

        class Purse : Container {

        };

    }
}


#endif