#ifndef GRAPHE_H
#define GRAPHE_H
#include "Sommets.h"
#include "Aretes.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>
#include "svgfile.h"

class Graphe
{
public:

    Graphe(std::string nomFichier, bool ponderation);
    ~Graphe()
    {
        for (auto s : m_sommets)
            delete s;
    }
    void afficher(bool ponderation);
    double dijkirsta(size_t num_s0, size_t numF);
    double obtenirPoid(const Sommets* som1, const Sommets* som2);
    void centraliteDeProxUnSommet(size_t num_s0) ;
    void centraliteDeProxSommets() ;


private:
    /// Le réseau est constitué d'une collection de stations
    std::vector<Sommets*> m_sommets;
    std::vector<Aretes*> m_aretes;
    int m_orient;
    int m_taille;
    int m_ordre;
};

#endif // GRAPHE_H
