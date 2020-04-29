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
    int rep,rep2, changement =0;
    std::string fich, ponde;
    std::cout<<"nom du fichier a charger : ";
    std::cin>>fich;
    Graphe a(fich);
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

    while(1)
    {
        if(changement ==1)
        {
            std::cout<<"nom du fichier a charger : ";
            std::cin>>fich;
            changement = 0;
        }
        Graphe a(fich);
        if(rep==1)
        {
            std::cout<<"nom fichier ponderation : ";
            std::cin>>ponde;
            a.ponderation(ponde);
            rep=0;
        }
        do
        {
            std::cout<<"\nVoulez vous:\n\n1:\tUtiliser la centralite de vecteur propre\n2:\tUtiliser la centralite de degre\n3:\tUtiliser la centralite de proximite\n4:\tUtiliser la centralite d'intermediare\n5:\tAfficher\n6:\tCharger un nouveau graphe\n7:\tAppliquer une nouvelle ponderation au graphe\n8:\tSupprimer une arete\n9:\tQuitter\n";
            std::cin>>rep2;
        }
        while(rep2<1 || rep2>9);
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
            changement = 1;
            break;
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
