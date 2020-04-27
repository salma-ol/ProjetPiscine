#ifndef ARETES_H
#define ARETES_H
#include "Sommets.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>
#include "svgfile.h"

class Aretes
{
    public:
        Aretes(int i);
        virtual ~Aretes();
        const Sommets* GetSommet1() const ;
        const Sommets* GetSommet2() const ;
        const double GetPoids() const ;
        const int GetNum()const ;
        std::pair<Sommets*,Sommets*>* getSommets();

        void SetSommet1(Sommets* num);
        void SetSommet2(Sommets* num);
        void SetPoids(double poids);
        void afficherArete(bool pond);


    private:
        std::pair < Sommets*, Sommets* > m_sommet;
        double m_poids;
        int m_num;
};

#endif // ARETES_H
