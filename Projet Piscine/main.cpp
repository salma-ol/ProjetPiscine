#include <iostream>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>
#include "Graphe.h"
#include "svgfile.h"

int main()
{
    int choix;
    try
    {
        do
        {
            do
            {
                std::cout << "Charger le fichier de ponderation ?\n1. Oui\n2. Non" << std::endl;
                std::cin >> choix;
            }
            while(choix <1 || choix >3);

            switch(choix)
            {
            case 1:
                {
                    Graphe g("piscine.txt", true);
                    g.afficher(1);
                    break;
                }
            case 2:
                {
                    Graphe graphe("piscine.txt", false);
                    graphe.afficher(0);
                    break;
                }
            }
        }
        while (choix != 3);
    }
    catch (const std::exception& e)
    {
        std::cerr << "Attention : " << e.what() << std::endl;
    }

    return 0;
}
