#include "Sommets.h"
#include "svgfile.h"

Sommets::Sommets(int i) : m_x{}, m_y{}, m_num{i}, m_name{}
{

}

Sommets::~Sommets()
{

}
const int Sommets::GetX() const
{
    return m_x;
}

const int Sommets::GetY() const
{
    return m_y;
}

const int Sommets::GetNum() const
{
    return m_num;
}

const std::string Sommets::GetName() const
{
    return m_name;
}

void Sommets::SetX(int x)
{
    m_x = x;
}

void Sommets::SetY(int y)
{
    m_y = y;
}

void Sommets::SetName(std::string name)
{
    m_name = name;
}

void Sommets::afficherSommet()
{
    std::cout << "Sommet " << m_num << " : ";
    std::cout << m_name << " " << m_x << " " << m_y << std::endl;
}

const std::vector<const Sommets*>& Sommets::getSuccesseurs() const
{
        return m_successeurs;
}

void Sommets::ajouterSucc(const Sommets* s)
{
    m_successeurs.push_back(s);
}
