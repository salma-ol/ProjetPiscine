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

    Graphe();
    Graphe(std::string nomFichier);
    ~Graphe()
    {
        for (auto s : m_sommets)
            delete s;
    }
    void ponderation(std::string);
    void afficher();
    void centraliteDegre();
    void supprimerArete() ;
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
    void setOrient(int a)
    {
        m_orient=a;
    }
    void setOrdre(int a)
    {
        m_ordre=a;
    }
    void setTaille(int a)
    {
        m_taille=a;
    }
    double dijkstra(size_t num_s0, size_t numF);
    double obtenirPoid(const Sommets* som1, const Sommets* som2);
    void centraliteDeProxUnSommet(size_t num_s0, Sommets* Actuel) ;
    void centraliteDeProxSommets() ;

    void VecteurPropre();
    void Intermediarite();
    Graphe operator=(Graphe const&);

private:
    /// Le réseau est constitué d'une collection de stations
    std::vector<Sommets*> m_sommets;
    std::vector<Aretes*> m_aretes;
    int m_orient;
    int m_taille;
    int m_ordre;
    bool m_pondere;
};

#endif // GRAPHE_H
