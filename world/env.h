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

        class Environment : kris::util::CommandHandler {
        protected:
            entities::Container items;

            Environment* n_N;
            Environment* n_E;
            Environment* n_S;
            Environment* n_W;


        public:
            Environment() {};

            virtual bool handleCommand(std::string &);

            virtual std::string directions() = 0;
            virtual Environment*  neighbor(Direction& direction);
            virtual std::string description() = 0;

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
            const std::string _directions;
            const std::string _description;

        public:
            GenericRoom(std::string _directions, std::string _description)
                    : _directions(_directions), _description(_description) {

            }

            virtual std::string directions();
            virtual std::string description();
        };


    }
}


#endif