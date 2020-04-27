#include "Sommets.h"
#include "svgfile.h"

Sommets::Sommets(int i) : m_x{}, m_y{}, m_num{i}, m_indice{1.0},m_indicenormalise{0.0}, m_name{}
{

}

Sommets::~Sommets()
{

}
int Sommets::GetX()
{
    return m_x;
}

int Sommets::GetY()
{
    return m_y;
}

int Sommets::GetNum()
{
    return m_num;
}

std::string Sommets::GetName()
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

void Sommets::setIndice(float a)
{
    m_indice=a;
}

float Sommets::getIndice()
{
    return m_indice;
}

float Sommets::getIndiceNormalise()
{
    return m_indicenormalise;
}

void Sommets::setIndiceNormalise(float a)
{
    m_indicenormalise=a;
}
