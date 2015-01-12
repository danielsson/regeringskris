

#ifndef ENTITY_GUARD
#define ENTITY_GUARD

#include <vector>
#include <map>
#include "../util.h"

namespace kris {
    namespace entities {

        enum Party {
            VPK, S, MP, C, KD, FP, M, SD, FI, P
        };


        struct KabbalaAttack {
            std::string message;
            int sjalvaktning_modifier;
            int resistance_modifier;
            int probability;


            KabbalaAttack(int probability, int resistance_modifier, int sjalvaktning_modifier, std::string message)
                    : probability(probability),
                      resistance_modifier(resistance_modifier),
                      sjalvaktning_modifier(sjalvaktning_modifier),
                      message(message) {
            }
        };


        class Entity {
        protected:
            std::string id;
        public:
            static std::string type();

            std::string const &getId() const {
                return id;
            }

            void setId(std::string &id) {
                Entity::id = id;
            }
        };



        /*
            ITEMS
         */


        class Physible : public Entity {

        protected:
            std::string _name;
            std::string _desc;
            int weight = 1;
            bool moveable = true;

        public:
            virtual std::string const &name() const;
            virtual std::string description() const;
            virtual int getWeight() const;
            virtual bool use();

            bool isMoveable() const {
                return moveable;
            }

            void setMoveable(bool moveable) {
                Physible::moveable = moveable;
            }
        };



        class Container : public Physible {


        protected:
            std::vector<entities::Physible*> items;

        public:
            enum TransferError {
            Full, NotFound, Immovable, OK
            };

            void add_item(entities::Physible* item) {
                items.push_back(item);
            }

            entities::Physible* get_item(const std::string& name);
            virtual std::string type();

            virtual std::string description() const;
            virtual TransferError transfer_to(const std::string& name, Container & other);

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


        class Hero;


        class Actor : public Entity {
        protected:
            std::string _name;
            std::string _description;
            std::string image_name;

            Physible* _weakSpot;

            entities::Container items;

        public:
            Actor(std::string name, std::string desc, Physible* weakS);

            Actor(std::string name);
            virtual std::string const & name();
            virtual bool act();
            virtual bool offered(Physible *);
            virtual void rant();

            virtual std::string describe();

            virtual void kabbla(Hero * hero);

            std::string const &getImageName() const {
                return image_name;
            }

            void setImageName(std::string &image_name) {
                Actor::image_name = image_name;
            }

            entities::Container &getItems() {
                return items;
            }
        };


        class Politician : public Actor {
        protected:
            bool _givenConsent;
            Party affiliation;
            int resistancePoints = 0;

            std::vector<KabbalaAttack> attacks;

        public:
            static std::map<std::string, Party> partyMapping;

            static std::map<Party, std::string> partyMappingReversed;

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
            virtual void kabbla(Hero * hero);

            Party getAffiliation() {
                return affiliation;
            }

            /**
            * How resistant are this politician against your politics?
            */
            int getResistancePoints() const {
                return resistancePoints;
            }

            void setResistancePoints(int resistancePoints) {
                Politician::resistancePoints = resistancePoints;
            }


            std::vector<KabbalaAttack> const &getAttacks() const {
                return attacks;
            }

            void setAttacks(std::vector<KabbalaAttack> &attacks) {
                Politician::attacks = attacks;
            }
        };


        class Hero : public Actor {

        public:

            Hero(std::string name) : Actor(name) {};
            static std::string type();

        };

    }
}


#endif