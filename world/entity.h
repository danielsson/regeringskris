

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


            KabbalaAttack(int probability, int resistance_modifier, int sjalvaktning_modifier, std::string message);
        };


        class Entity {
        protected:
            std::string id;
        public:

            std::string const &getId() const;
            void setId(std::string &id);

            virtual ~Entity();
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
            bool iequals(const std::string&, const std::string&);

            bool isMoveable() const;

            void setMoveable(bool moveable);
        };



        class Container : public Physible {


        protected:
            std::vector<entities::Physible*> items;

        public:
            enum TransferError {
            Full, NotFound, Immovable, OK
            };

            void add_item(entities::Physible* item);

            entities::Physible* get_item(const std::string& name);
            virtual std::string type();

            virtual std::string description() const;
            virtual TransferError transfer_to(const std::string& name, Container & other);

        };




        class GenericItem : public Physible {
        public:

            GenericItem(std::string _name, std::string _desc, int _weight);

        };

        class Purse : Container {

        };

        class HolyArtifact : public Physible {
            virtual bool use();


        public:
            HolyArtifact(std::string _name, std::string _desc);
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

            virtual std::string type();
            std::string const &getImageName() const;

            void setImageName(std::string &image_name);

            entities::Container &getItems() ;
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
            Politician(std::string str, std::string _desc, Party affiliation);
            virtual void giveConsent();
            virtual void rant();
            bool consent();
            virtual std::string describe();
            virtual void kabbla(Hero * hero);

            Party getAffiliation();

            virtual std::string type();

            /**
            * How resistant are this politician against your politics?
            */
            int getResistancePoints() const ;

            void setResistancePoints(int resistancePoints);


            std::vector<KabbalaAttack> const &getAttacks() const;
            void setAttacks(std::vector<KabbalaAttack> &attacks);
        };

        class Oracle : public Actor {


        public:
            virtual bool act();
            Oracle(std::string &name, std::string &desc, Physible *weakS);
        };


        class Hero : public Actor {

        public:

            Hero(std::string name);

        };

    }
}


#endif