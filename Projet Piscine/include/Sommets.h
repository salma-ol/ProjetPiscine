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
        const int GetX() const;
        const int GetY() const;
        const int GetNum() const ;
        const std::string GetName() const ;
        void SetX(int x);
        void SetY(int y);
        void SetName(std::string name);
        void afficherSommet();
        const std::vector<const Sommets*>& getSuccesseurs() const ;
        void ajouterSucc(const Sommets* s);

    private:
        int m_x;
        int m_y;
        int m_num;
        std::string m_name;
        std::vector<const Sommets*> m_successeurs ;
};

#endif // SOMMETS_H
