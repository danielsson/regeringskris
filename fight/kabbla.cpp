#include "kabbla.h"
#include "../world/env.h"
#include "../world/entity.h"
#include "../json/json.h"
#include "../util.h"

using namespace kris;
using namespace kris::env;
using namespace kris::entities;
using namespace kris::util;
using namespace kris::kabbala;


void KabblaMinigame::contestant_move() {
    std::cout << ">>>>>>>>>>>>>>>>>>>>>>>>>>>>> " << contestant->name() << "s drag\n";

    int r = rand() % 100;

    if (r < 33) {
        std::cout << contestant->name() << " kallade dig för en tölp i aftonbladet.\n";
        std::cout << "Det är effektivt\n";
        sjalvaktning -= 30;
    } else if(r < 90) {
        std::cout << contestant->name() << " gav dig en kolbit.\n";
        sjalvaktning -= 10;
        hero->getItems().add_item(new entities::GenericItem("Kolbit", "En helt vanlig kolbit. Eller ett iskallt politiskt mordvapen.", 1));
    } else {
        std::cout << contestant->name() << " snackade skit om dig, men råkade göra en pudel.\n";
        sjalvaktning += 50;
        contestant->setResistancePoints(contestant->getResistancePoints() - 126);
    }
}


void KabblaMinigame::kabbla() {
    std::cout << "Bring it on!\n";

    if (contestant->getImageName().size() > 0) {

        std::string image = Util::get_file_contents("people/" + contestant->getImageName());
        std::cout << image << std::endl;
    }

    std::cout << "Du måste övertyga Annie om att acceptera er budget!\n";

    while (isPlaying && contestant->getResistancePoints() > 0) {

        std::cout << "<<<<<<<<<<<<<<<<<<<<<<<<<<<<< Ditt drag\n";
        std::cout << contestant->name() << " har en resistance på " << contestant->getResistancePoints() << std::endl;
        std::cout << "Du har en självaktning på " << sjalvaktning << std::endl << std::endl;

        std::cout << "Din tur!\n";
        std::cout << "Möjliga drag:\n";
        std::cout << "\t slåss : Förfall till handgemäng\n";
        std::cout << "\t gåva : ge " << contestant->name() << " en gåva\n";
        std::cout << "\t fly : Skrik 'CHARLIE HEBDO' och fly i förvirringen när alla försöker förklara hur viktigt de tycker att det är med yttrandefrihet.\n";
        std::cout << "\t inventera : Kontrollera dina fickor\n";
        std::cout << "\t smutskasta : Snacka skit om " << contestant->name() << " bakom dess rygg\n";

        std::cout << "Käbbel :> ";
        std::string cmd;
        std::getline(std::cin, cmd);

        if (cmd == "fly") {
            std::cout << "Du rymde i tumultet som uppstod.\n";
            isPlaying = false;
            break;
        }

        if (cmd == "slåss") {
            std::cout << "Vad är pk nog att göra nu?\n";
            sjalvaktning = 0;
        } else if (cmd == "gåva") {
            std::cout << "TBI" << std::endl;
            contestant->setResistancePoints(contestant->getResistancePoints() - 100);
            sjalvaktning += 20;
        } else if (cmd == "inventera") {
            std::cout << hero->getItems().description();
        } else if (cmd == "smutskasta") {
            std::cout << "Du kallade " << contestant->name() << " för en osamarbetsvillig toffel i expressen.";
            contestant->setResistancePoints(contestant->getResistancePoints() + 100);
            sjalvaktning -= 10;
        } else {
            std::cout << "Det var inget alternativ!" << std::endl;
        }

        contestant_move();
    }

    if (contestant->getResistancePoints() < 0) {
        std::cout << "Grattis, du övertygade " << contestant->name() << " om att rösta på ert budgetförslag!\n";

    } else {
        std::cout << "Det är bara en massa käbbel!!" << std::endl;
    }

}
