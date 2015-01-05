#import <iostream>

#ifndef UTIL_GUARD
#define UTIL_GUARD

namespace Kris {
    namespace Util {

        class CommandHandler {

        protected:
            std::string readWord(std::string &);

        public:
            virtual bool handleCommand(std::string &) = 0;
        };
    }
}

#endif