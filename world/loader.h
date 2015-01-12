#include <iostream>
#include <fstream>
#include "../json/json.h"
#include "env.h"
#include "entity.h"

#ifndef LOADER_GUARD
#define LOADER_GUARD

using namespace kris::env;
using namespace kris::entities;

using json = nlohmann::json;

namespace kris {

    class Loader {

    protected:
        std::string file_path;
        std::vector<Actor *> actors;
        std::vector<Physible *> physibles;
        std::vector<Environment *> envs;

        void read_item(json &obj, Environment* env);
        std::vector<KabbalaAttack> read_attacks(json & obj, Politician * pol);
        void read_actor(json & obj, Environment * environment);
        void read_environment(json &obj, std::map<std::string, Environment *> &environments);
        void read_environments(json &obj, std::map<std::string, Environment *> &environments);
        void read_neighbors(json &obj, std::map<std::string, Environment *> &environments);

    public:
        Loader(std::string);
        Environment* construct();

        void add_managed_pointer(Actor * ptr);
        void add_managed_pointer(Physible * ptr);
        void add_managed_pointer(Environment * ptr);

        ~Loader();

        std::vector<Environment *> &getEnvs() {
            return envs;
        }

        std::vector<Physible *> &getPhysibles() {
            return physibles;
        }

        std::vector<Actor *> &getActors() {
            return actors;
        }
    };


}



#endif