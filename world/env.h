

#ifndef ENV_GUARD
#define ENV_GUARD

#include <vector>
#include "../util.h"
#include "entity.h"
#include <map>

namespace kris {

    namespace env {
        enum Direction {
            N, E, S, W


        };


        class Environment {

        protected:
            entities::Container items;
            std::map<std::string, entities::Actor*> actors;


            Environment* n_N = 0;
            Environment* n_E = 0;
            Environment* n_S = 0;
            Environment* n_W = 0;

            std::string _description;
            std::string _name;

        public:
            Environment() {};

            virtual std::string directions() const;
            virtual Environment*  neighbor(Direction& direction) const;
            virtual void set_neighbor(Direction d, Environment *);
            virtual std::string description() const;
            virtual std::string name() const = 0;

            static std::string type();

            virtual void onEntry(entities::Actor*);

            /**
            * Returns true to block departure.
            */
            virtual bool onDeparture(entities::Actor*);

            virtual void onPick(entities::Physible*);
            virtual void onDrop(entities::Physible*);

            virtual ~Environment() {};


            entities::Container& getItems();
            entities::Container const& getItems() const;

            std::map<std::string, entities::Actor*> & getActors();
            std::map<std::string, entities::Actor*> const &getActors() const;

            static Direction fromString(std::string);
        };

        class OutdoorEnv : public Environment {

        };


        class IndoorEnv : public Environment {

        };

        class GenericRoom : public IndoorEnv {

        protected:
            std::string _directions;

        public:
            GenericRoom(std::string name, std::string _description);

            virtual std::string name() const;

            static std::string type() ;

        };


    }
}


#endif