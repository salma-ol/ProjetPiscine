#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>
#include "sauvegarde.h"
#include "Graphe.h"
#include "svgfile.h"

int main()
{
<<<<<<< Updated upstream
    charger();
=======
    int rep;
    std::string fich;
    std::cout<<"nom du fichier a charger : ";
    std::cin>>fich;
    Graphe a(fich);
    do
    {
        std::cout<<"voulez-vous charger une pondération:\n1.oui\n2.non\n";
        std::cin>>rep;
    }while(rep!=1 && rep!=2);
    if(rep==1)
    {
        std::cout<<"nom fichier ponderation : ";
        std::cin>>fich;
        a.ponderation(fich);
    }
    a.afficher();
    a.VecteurPropre();
    a.centraliteDegre();
    a.centraliteDeProxSommets();
    a.Intermediarite();
>>>>>>> Stashed changes
    return 0;
}
