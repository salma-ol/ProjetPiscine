#ifndef SOMMETS_H
#define SOMMETS_H
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>
#include "svgfile.h"

class Sommets
{
    public:
        Sommets(int i);
        ~Sommets();
        int GetX();
        int GetY();
        int GetNum();
        std::string GetName();
        void SetX(int x);
        void SetY(int y);
        void SetName(std::string name);
        void afficherSommet();

    private:
        int m_x;
        int m_y;
        int m_num;
        int m_indice;
        std::string m_name;
};

#endif // SOMMETS_H
