#include <vector>
#include "../util.h"
#include "entity.h"

#ifndef ENV_GUARD
#define ENV_GUARD

namespace kris {
    namespace env {
        enum Direction {
            N, E, S, W
        };

        class Environment {
        protected:
            entities::Container items;

            Environment* n_N;
            Environment* n_E;
            Environment* n_S;
            Environment* n_W;

            std::string _description;
            std::string _name;

        public:
            Environment() {};

            virtual std::string directions();
            virtual Environment*  neighbor(Direction& direction);
            virtual std::string description();
            virtual std::string name() = 0;

            virtual void onEntry(entities::Actor);

            /**
            * Returns true to block departure.
            */
            virtual bool onDeparture(entities::Actor);

            virtual void onPick(entities::Physible);
            virtual void onDrop(entities::Physible);


            entities::Container& getItems() {
                return items;
            }
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

        };


    }
}


#endif