#include "Aretes.h"
#include "svgfile.h"

Aretes::Aretes(int i, Sommets*a,Sommets*b): m_sommet{std::make_pair(a,b)}, m_poids{1},m_num{i}
{}

Aretes::~Aretes()
{}

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

const int Aretes::GetNum() const
{
    return m_num;
}
const double Aretes::GetPoids() const
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

void Aretes::SetNum(int num)
{
    m_num=num ;
}

