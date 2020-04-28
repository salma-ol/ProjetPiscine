/*#include "sauvegarde.h"
#include "Graphe.h"
#include <iostream>
Graphe charger()
{
    Graphe g;
    int choix;
    std::string fichier, fichier_pond;
    try
    {
            do
            {
                std::cout << "Veuillez saisir le nom de votre fichier\n" << std::endl;
                std::cin >> fichier;
                std::cout << "Voulez-vous charger le fichier de ponderation ?\n1. Oui\n2. Non" << std::endl;
                std::cin >> choix;
            }
            while(choix <1 || choix >2);

            switch(choix)
            {
            case 1:
                {
                    std::cout << "Veuillez saisir le nom de votre fichier de ponderation\n"<<std::endl;
                    std::cin >> choix;
                    Graphe gr("piscine.txt", true);
                    g=gr;
                    //g.afficher(1);
                    break;
                }
            case 2:
                {
                    Graphe gr("piscine.txt", false);
                    g=gr;
                    //g.afficher(0);
                    break;
                }
            }
    }
    catch (const std::exception& e)
    {
        std::cerr << "Attention : " << e.what() << std::endl;
    }
    return g;
}
*/
