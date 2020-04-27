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
        float getIndice();
        float getIndiceNormalise();
        std::string GetName();
        void SetX(int x);
        void SetY(int y);
        void SetName(std::string name);
        void setIndice(float a);
        void setIndiceNormalise(float a);
        void afficherSommet();

    private:
        int m_x;
        int m_y;
        int m_num;
        float m_indice;
        float m_indicenormalise;
        std::string m_name;
};

#endif // SOMMETS_H
