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
    bool prems=true;
    int rep;
    Graphe a;
    std::string fich;
    while(1)
    {
        if(prems)
        {
            std::cout<<"nom du fichier a charger : ";
            std::cin>>fich;
            Graphe gr(fich);
            a=gr;
            do
            {
                std::cout<<"voulez-vous charger une pondération:\n1.oui\n2.non\n";
                std::cin>>rep;
            }
            while(rep!=1 && rep!=2);
            if(rep==1)
            {
                std::cout<<"nom fichier ponderation : ";
                std::cin>>fich;
                a.ponderation(fich);
            }
            else{}
        }
        prems=false;
        do
        {
            std::cout<<"\nVoulez vous:\n1:utiliser la centralite de vecteur propre\n2:utiliser la centralite de degre\n3:utiliser la centralite de proximite\n4:utiliser la centralite d'intermediare\n5:afficher\n6:charger un nouveau graphe\n7:aplliquer une nouvelle ponderation au graphe\n8:quitter\n";
            std::cin>>rep;
        }while(rep<1 || rep>8);
        switch(rep)
        {
        case 1:
            a.VecteurPropre();
            break;
        case 2:
            a.centraliteDegre();
            break;
        case 3:
            a.centraliteDeProxSommets();
            break;
        case 4:
            a.Intermediarite();
            break;
        case 5:
            a.afficher();
            break;
        case 6:
            prems=true;
            break;
        case 7:
            std::cout<<"nom du fichier : ";
            std::cin>>fich;
            a.ponderation(fich);
            break;
        case 8:
            return 0;
            break;
        default:
            break;
        }
        std::cout<<"\n";
    }
    return 0;
}
