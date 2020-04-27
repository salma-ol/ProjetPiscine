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
    int getOrdre()
    {
        return m_ordre;
    }
    int getTaille()
    {
        return m_taille;
    }
    int getOrient()
    {
        return m_orient;
    }
    std::vector<Sommets*> *getSommets()
    {
        return &m_sommets;
    }
    std::vector<Aretes*> *getAretes()
    {
        return &m_aretes;
    }
    int setOrient(int a)
    {
        m_orient=a;
    }
    int setOrdre(int a)
    {
        m_ordre=a;
    }
    int setTaille(int a)
    {
        m_taille=a;
    }

private:
    /// Le réseau est constitué d'une collection de stations
    std::vector<Sommets*> m_sommets;
    std::vector<Aretes*> m_aretes;
    int m_orient;
    int m_taille;
    int m_ordre;
};

#endif // GRAPHE_H
