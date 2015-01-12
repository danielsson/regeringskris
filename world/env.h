

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

            virtual std::string directions();
            virtual Environment*  neighbor(Direction& direction);
            virtual void set_neighbor(Direction d, Environment *);
            virtual std::string description();
            virtual std::string name() = 0;

            static std::string type();

            virtual void onEntry(entities::Actor*);

            /**
            * Returns true to block departure.
            */
            virtual bool onDeparture(entities::Actor*);

            virtual void onPick(entities::Physible*);
            virtual void onDrop(entities::Physible*);


            entities::Container& getItems() {
                return items;
            }

            std::map<std::string, entities::Actor*> & getActors() {
                return actors;
            }

            static Direction fromString(std::string);
        };

        class OutdoorEnv : public Environment {

        };


        class IndoorEnv : public Environment {

        };

        class Hemicycle : IndoorEnv {

        };

        class OpinionCorridor : IndoorEnv {

        };

        class GenericRoom : public IndoorEnv {

        protected:
            std::string _directions;

        public:
            GenericRoom(std::string name, std::string _description) {
                this->_name = name;
                this->_directions = _directions;
                this->_description = _description;
            }

            virtual std::string name() {
                return _name;
            }

            static std::string type() {
                return "GenericRoom";
            }

        };


    }
}


#endif