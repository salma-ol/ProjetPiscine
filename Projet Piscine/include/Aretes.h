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
        Sommets* GetSommet1();
        Sommets* GetSommet2();
        double GetPoids();
        int GetNum();
        void SetSommet1(Sommets* num);
        void SetSommet2(Sommets* num);
        void SetPoids(double poids);
        void afficherArete(bool pond);


    private:
        std::pair < Sommets*, Sommets* > m_sommet;
//        Sommets* m_sommet1;
//        Sommets* m_sommet2;
        double m_poids;
        int m_num;
};

#endif // ARETES_H
