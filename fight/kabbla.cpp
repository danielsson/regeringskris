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

std::pair<std::string, int> KabblaMinigame::getNewspaper() {
    switch (rand() % 11) {
        case 0: return std::pair<std::string, int>("Aftonbladet", 8);
        case 1: return std::pair<std::string, int>("Expressen", 3);
        case 2: return std::pair<std::string, int>("Dagens Nyheter", 1);
        default:
        case 3: return std::pair<std::string, int>("Dagens Industri", 6);
        case 4: return std::pair<std::string, int>("Metro", 4);
        case 5: return std::pair<std::string, int>("Fria Tider", -10);
        case 6: return std::pair<std::string, int>("en våtservett", 0);
        case 7: return std::pair<std::string, int>("Nyheter24", rand() % 5);
        case 8: return std::pair<std::string, int>("New York Times", 15);
        case 9: return std::pair<std::string, int>("Historieätarna", 15);
        case 10:return std::pair<std::string, int>("SVT Rapport", 10);
    }
}

std::string KabblaMinigame::getComparison() {
    switch (rand() % 20) {
        case 0: return "toffel";
        case 1: return "saltgurka";
        case 2: return "hal ål";
        default:
        case 3: return "fascist";
        case 4: return "poltergeist";
        case 5: return "termos";
        case 6: return "loka";
        case 7: return "hippie";
        case 8: return "buss utan hjul";
        case 9: return "adam sandler";
        case 10: return "foliehatt";
        case 11: return "elakast";
        case 12: return "tjock";
        case 13: return "känslokall";
        case 14: return "landsmoder";
        case 15: return "avpolleterad";
        case 16: return "oomkullvältelig";
        case 17: return "fritös";
        case 18: return "bänkens prydnad";
        case 19: return "tarvligt kräk";
            //case 0: return std::pair<std::string, int>("Aftonbladet", 10);

    }
}

/**
* Uses the pobability value to do a weighted random select amongst the attacks.
*/
KabbalaAttack const &  KabblaMinigame::pick_at_random(std::vector<KabbalaAttack> const &attacks) {
    int total_sum = 0;

    for (KabbalaAttack const & k : attacks)  {
        total_sum += k.probability;
    }

    int pick_k = rand() % total_sum;

    int cumulative_sum = 0;
    for (KabbalaAttack const & k : attacks) {
        cumulative_sum += k.probability;
        if (cumulative_sum > pick_k) {
            return k;
        }
    }

    return attacks[attacks.size()-1];

}

void KabblaMinigame::contestant_move() {
    std::cout << ">>>>>>>>>>>>>>>>>>>>>>>>>>>>> " << contestant->name() << "s drag\n";

    if (contestant->getAttacks().size() > 0) {
        KabbalaAttack a = pick_at_random(contestant->getAttacks());
        std::cout << a.message << std::endl;
        std::cout << "> Din självaktning: " << a.sjalvaktning_modifier
                << " | " << contestant->name() << "s resistans: " << a.resistance_modifier << std::endl;

        sjalvaktning += a.sjalvaktning_modifier;
        contestant->setResistancePoints(contestant->getResistancePoints() + a.resistance_modifier);

    } else {
        int r = rand() % 100;

        if (r < 33) {
            std::cout << contestant->name() << " kallade dig för en tölp i aftonbladet.\n";
            std::cout << "Det är effektivt\n";
            sjalvaktning -= 30;
        } else if (false) {
            std::cout << contestant->name() << " gav dig en kolbit.\n";
            sjalvaktning -= 10;
            GenericItem *item = new entities::GenericItem("Kolbit", "En helt vanlig kolbit. Eller ett iskallt politiskt mordvapen.", 1);

            hero->getItems().add_item(item);
        } else {
            std::cout << contestant->name() << " snackade skit om dig, men råkade göra en pudel.\n";
            sjalvaktning += 50;
            contestant->setResistancePoints(contestant->getResistancePoints() - 126);
        }
    }
}

void KabblaMinigame::print_status() {
    std::cout << "<<<<<<<<<<<<<<<<<<<<<<<<<<<<< Ditt drag\n";
    std::cout << contestant->name() << " har en resistance på " << contestant->getResistancePoints() << std::endl;
    std::cout << "Du har en självaktning på " << sjalvaktning << std::endl << std::endl;

    std::cout << "Din tur!\n";
    std::cout << "Möjliga drag:\n";
    std::cout << "\t debatt     Bjud in till SVT-debatt\n";
    std::cout << "\t gåva       Ge " << contestant->name() << " en gåva\n";
    std::cout << "\t fly        Skrik 'CHARLIE HEBDO' och fly i förvirringen när alla försöker förklara hur viktigt de tycker att det är med yttrandefrihet.\n";
    std::cout << "\t inventera  Kontrollera dina fickor\n";
    std::cout << "\t smutskasta Snacka skit om " << contestant->name() << " bakom hens rygg\n";
}

void KabblaMinigame::kabbla() {
    std::cout << "Bring it on!\n";
    int beginning_resistance = contestant->getResistancePoints();

    if (contestant->getImageName().size() > 0) {

        std::string image = Util::get_file_contents("people/" + contestant->getImageName());
        std::cout << image << std::endl;
    }

    std::cout << "Du måste övertyga " << contestant->name() << " om att acceptera er budget!\n";

    while (isPlaying && contestant->getResistancePoints() > 0 && sjalvaktning > 0) {

        print_status();

        std::cout << "Käbbel :> ";
        std::string cmd;
        std::getline(std::cin, cmd);

        if (cmd == "fly") {
            std::cout << "Du rymde i tumultet som uppstod.\n";
            isPlaying = false;
            break;
        }

        if (cmd == "debatt") {
            fight();

        } else if (cmd == "gåva") {
            gift();
        } else if (cmd == "inventera") {
            std::cout << hero->getItems().description();
        } else if (cmd == "smutskasta") {
            do_dirty_laundry();
        } else {
            std::cout << "Det var inget alternativ!" << std::endl;
        }

        contestant_move();
    }

    if (sjalvaktning <= 0) {
        std::cout << "Å nej, du har slut på självaktning. Synd.\n";
        contestant->setResistancePoints(beginning_resistance);
    }

    if (contestant->getResistancePoints() <= 0) {
        std::cout << "Grattis, du övertygade " << contestant->name() << " om att rösta på ert budgetförslag!\n";
        contestant->giveConsent();

    } else {
        std::cout << "Det är bara en massa käbbel!!" << std::endl;
    }

}

void KabblaMinigame::do_dirty_laundry() {
    std::pair<std::string, int> paper = getNewspaper();
    std::cout << "Du kallade " << contestant->name() << " för " << getComparison()
    << " i " << paper.first << std::endl;

    std::cout << "> Din självaktning: " << 10 * paper.second
            << " | " << contestant->name() << "s resistans: " << (-10 * paper.second) << std::endl;

    contestant->setResistancePoints(contestant->getResistancePoints() - 10 * paper.second);
    sjalvaktning += 10 * paper.second;
}

void KabblaMinigame::gift() {
    std::string thing;
    std::cout << "Dina inventarier: \n";
    std::cout << hero->getItems().description();
    std::cout << " Vad vill du ge bort? :> ";
    std::getline(std::cin, thing);

    Physible* p = hero->getItems().get_item(thing);

    if (p) {
        std::cout << "Du gav " << p->name() << " till " << contestant->name() << std::endl;
        hero->getItems().transfer_to(p->name(), contestant->getItems());


        if (p->getId() == "@penna") {
            std::cout << "Du gav bort en glitterpenna och vann därför debatten omedelbart.\n";
            std::cout << "> Din självaktning: " << 100
                    << " | " << contestant->name() << "s resistans: " << (-1 * contestant->getResistancePoints()) << std::endl;

            sjalvaktning = 100;
            contestant->setResistancePoints(0);

        } else {
            std::cout << contestant->name() << ": 'Vad fan är det här? Nåja, tack eller whatever.'\n";
        }
    } else {
        std::cout << "Du försökte ge bort en " << thing << " men hade ingen sådan.\n";
        std::cout << contestant->name() << " var föga imponerad av gesten.\n";
    }



}

void KabblaMinigame::fight() {
    std::cout << "Dags för debatt i SVT Agenda mellan dig och " << contestant->name() << std::endl;

    int xv = rand() % 100;

    if (hero->getItems().get_item("Kolbit") && xv > 30) {
        std::cout << "Du viftade med kolbiten och vann därför debatten omedelbart.\n";
        hero->getItems().transfer_to("Kolbit", contestant->getItems());
        std::cout << "> Din självaktning: " << 100
                << " | " << contestant->name() << "s resistans: " << (-1 * contestant->getResistancePoints()) << std::endl;

        sjalvaktning = 100;
        contestant->setResistancePoints(0);

    } else if(contestant->getItems().get_item("Kolbit") && xv > 50) {
        std::cout << contestant->name() << " viftade med en kolbit och besegrade dig hårt.\n";
        contestant->getItems().transfer_to("Kolbit", hero->getItems());
    }


    std::pair<std::string, int> paper = getNewspaper();

    if (xv % 6 == 2) {
        std::cout << paper.first << " skriver att vad du förmodligen menade när du sade att gemenskapen ska stärkas, egentligen är antisemtiskt. \n";
        std::cout << "> Din självaktning: " << (-3 * paper.second)
                << " | " << contestant->name() << "s resistans: " << (3 * paper.second) << std::endl;

        sjalvaktning -= 3 * paper.second;
        contestant->setResistancePoints(contestant->getResistancePoints() + 3 * paper.second);
    }

    if (xv % 2 == 0) {
        std::cout << "Göran Greider hyllar din debatt i " << paper.first << std::endl;
        std::cout << "> Din självaktning: " << (10 * paper.second)
                << " | " << contestant->name() << "s resistans: " << (-100 * paper.second) << std::endl;

        sjalvaktning += 10 * paper.second;
        contestant->setResistancePoints(contestant->getResistancePoints() - 100 * paper.second);
    }


}


