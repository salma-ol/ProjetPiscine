#include "Aretes.h"
#include "svgfile.h"

Aretes::Aretes(int i) : m_num{i}
{
    //ctor
}

Aretes::~Aretes()
{
    //dtor
}

void Aretes::SetSommet1(Sommets* num)
{
    m_sommet.first = num;
}

void Aretes::SetPoids(double poids)
{
    m_poids = poids;
}

void Aretes::SetSommet2(Sommets* num)
{
    m_sommet.second = num;
}
Sommets* Aretes::GetSommet1()
{
    return m_sommet.first;
}

Sommets* Aretes::GetSommet2()
{
    return m_sommet.second;
}

int Aretes::GetNum()
{
    return m_num;
}
double Aretes::GetPoids()
{
    return m_poids;
}
void Aretes::afficherArete(bool pond)
{
    std::cout << "Arete " << m_num << " : ";
    std::cout << m_sommet.first->GetNum() << " " << m_sommet.second->GetNum() << std::endl;
    if(pond == true)
    {
        std::cout << "Poids : " << m_poids << std::endl;
    }
}


std::pair<Sommets*,Sommets*>* Aretes::getSommets()
{
    return &m_sommet;
}
