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
    int rep, rep2;
    std::string fich, ponde;
    std::cout<<"nom du fichier a charger : ";
    std::cin>>fich;
    Graphe a(fich);
    do
    {
        std::cout<<"voulez-vous charger une ponderation:\n1.oui\n2.non\n";
        std::cin>>rep;
    }while(rep!=1 && rep!=2);

    while(1)
    {
        if(rep==1)
        {
            std::cout<<"nom fichier ponderation : ";
            std::cin>>ponde;
            a.ponderation(ponde);
            rep=0;
        }
        do
        {
            std::cout<<"\nVoulez vous:\n1:utiliser la centralite de vecteur propre\n2:utiliser la centralite de degre\n3:utiliser la centralite de proximite\n4:utiliser la centralite d'intermediare\n5:afficher\n6:charger un nouveau graphe\n7:aplliquer une nouvelle ponderation au graphe\n8:supprimer une arete\n9:quitter\n";
            std::cin>>rep2;
        }while(rep2<1 || rep2>9);
        switch(rep2)
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
            {
                std::cout<<"nom du fichier a charger : ";
                std::cin>>fich;
                do
                {
                    std::cout<<"voulez-vous charger une ponderation:\n1.oui\n2.non\n";
                    std::cin>>rep;
                }while(rep!=1 && rep!=2);
                Graphe Gr(fich);
                a=Gr;
                break;
            }
        case 7:
            rep=1;
            break;
        case 8:
            a.supprimerArete();
            break;
        case 9:
            return 0;
            break;
        default:
            break;
        }
        std::cout<<"\n";
        rep2=0;
    }
    return 0;
}
