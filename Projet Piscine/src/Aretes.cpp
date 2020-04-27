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
const Sommets* Aretes::GetSommet1() const
{
    return m_sommet.first;
}

const Sommets* Aretes::GetSommet2() const
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
