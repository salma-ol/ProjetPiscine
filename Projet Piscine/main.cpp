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
<<<<<<< Updated upstream
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
=======
    int rep, rep2, changement =1;
    std::string fich, ponde;



    while(1)
    {
        if(changement == 1)
        {
            std::cout<<"nom du fichier a charger : ";
            std::cin>>fich;
            changement =0;
=======
    int rep, rep2, changement = 1;
    std::string fich, ponde;
    while(1)
    {
        if(changement ==1)
        {
            std::cout<<"nom du fichier a charger : ";
            std::cin>>fich;
            changement = 0;
>>>>>>> Stashed changes

            do
            {
                std::cout<<"voulez-vous charger une ponderation:\n1.oui\n2.non\n";
                std::cin>>rep;
            }
            while(rep!=1 && rep!=2);
        }
        Graphe a(fich);

<<<<<<< Updated upstream

=======
>>>>>>> Stashed changes
        if(rep==1)
        {
            std::cout<<"nom fichier ponderation : ";
            std::cin>>ponde;
            a.ponderation(ponde);
            rep=0;
        }
        do
        {
<<<<<<< Updated upstream
            std::cout<<"\nVoulez vous:\n1:\tUtiliser la centralite de vecteur propre\n2:\tUtiliser la centralite de degre\n3:\tUtiliser la centralite de proximite\n4:\tUtiliser la centralite d'intermediare\n5:\tAfficher\n6:\tCharger un nouveau graphe\n7:\tAppliquer une nouvelle ponderation au graphe\n8:supprimer une arete\n9:quitter\n";
            std::cin>>rep2;
        }
        while(rep2<1 || rep2>9 || changement == 1);
=======
            std::cout<<"\nVoulez vous:\n\n1:\tUtiliser la centralite de vecteur propre\n2:\tUtiliser la centralite de degre\n3:\tUtiliser la centralite de proximite\n4:\tUtiliser la centralite d'intermediare\n5:\tAfficher\n6:\tCharger un nouveau graphe\n7:\tAppliquer une nouvelle ponderation au graphe\n8:\tSupprimer une arete\n9:\tQuitter\n";
            std::cin>>rep2;
        }
        while(rep2<1 || rep2>9);
>>>>>>> Stashed changes
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
<<<<<<< Updated upstream
            changement = 1;
=======
            changement =1;
>>>>>>> Stashed changes
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
>>>>>>> Stashed changes
    }
    a.afficher();
    a.VecteurPropre();
    a.centraliteDegre();
    a.centraliteDeProxSommets();
    a.Intermediarite();
>>>>>>> Stashed changes
    return 0;
}
