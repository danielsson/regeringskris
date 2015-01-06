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
            std::vector<entities::Physible> items;

            std::shared_ptr<Environment> n_N;
            std::shared_ptr<Environment> n_E;
            std::shared_ptr<Environment> n_S;
            std::shared_ptr<Environment> n_W;


        public:
            Environment() {};

            virtual bool handleCommand(std::string &);

            virtual std::string directions() = 0;
            virtual std::shared_ptr<Environment>  neighbor(Direction direction);
            virtual std::string description() = 0;

            virtual void onEntry(entities::Actor);

            /**
            * Returns true to block departure.
            */
            virtual bool onDeparture(entities::Actor);

            virtual void onPick(entities::Physible);
            virtual void onDrop(entities::Physible);

            virtual void addItem(entities::Physible &);


            std::vector<entities::Physible> const &getItems() const {
                return items;
            }
        };

        class OutdoorEnv : protected Environment {

        };


        class IndoorEnv : protected Environment {

        };

        class Hemicycle : IndoorEnv {

        };

        class OpinionCorridor : IndoorEnv {

        };

        class GenericRoom : IndoorEnv {

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