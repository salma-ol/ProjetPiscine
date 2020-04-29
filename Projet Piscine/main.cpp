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
    int rep, rep2, changement =1, ponderation = 1;
    std::string fich, ponde;
    while(2)
    {
        if(changement == 1)
        {
            std::cout<<"nom du fichier a charger : ";
            std::cin>>fich;
            changement = 0;
        }
        Graphe a(fich);


        while(1 && changement == 0)
        {
            if(ponderation == 1)
            {
                do
                {
                    std::cout<<"voulez-vous charger une ponderation:\n1.oui\n2.non\n";
                    std::cin>>rep;
                    ponderation =0;
                }
                while(rep!=1 && rep!=2);
            }

            if(rep==1)
            {
                std::cout<<"nom fichier ponderation : ";
                std::cin>>ponde;
                a.ponderation(ponde);
                rep=0;
            }
            do
            {
                std::cout<<"\nVoulez vous:\n1:utiliser la centralite de vecteur propre\n2:utiliser la centralite de degre\n3:utiliser la centralite de proximite\n4:utiliser la centralite d'intermediare\n5:afficher\n6:charger un nouveau graphe\n7:appliquer une nouvelle ponderation au graphe\n8:supprimer une arete\n9:quitter\n";
                std::cin>>rep2;
            }
            while(rep2<1 || rep2>9);

            if(rep2 == 1)
            {
                a.VecteurPropre();
            }
            if(rep2 == 2)
            {
                a.centraliteDegre();
            }
            if(rep2 == 3)
            {
                a.centraliteDeProxSommets();
            }
            if(rep2 == 4)
            {
                a.Intermediarite();
            }
            if(rep2 == 5)
            {
                a.afficher();
            }
            if(rep2 == 6)
            {
                changement = 1;
            }
            if(rep2 == 7)
            {
                ponderation = 1;
                rep=1;
            }
            if(rep2 == 8)
            {
                a.supprimerArete();
            }
            if(rep2 == 9)
            {
                return 0;
            }
        }
    }
    return 0;
}
