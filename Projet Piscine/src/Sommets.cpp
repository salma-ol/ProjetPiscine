#include "Sommets.h"
#include "svgfile.h"

Sommets::Sommets(int i) : m_x{}, m_y{}, m_num{i}, m_name{}
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
<<<<<<< Updated upstream
=======


const std::vector<const Sommets*>* Sommets::getSuccesseurs() const
{
        return &m_successeurs;
}

void Sommets::ajouterSucc(const Sommets* s)
{
    m_successeurs.push_back(s);
}

void Sommets::SetIndiceDegreNN(float indice) // indice non normalise
{
    m_indices[0].first = indice;
}

float Sommets::GetIndiceDegreNN() const// indice non normalise
{
    return m_indices[0].first;
}

float Sommets::GetIndiceDegre() const // indice normalise
{
    return m_indices[0].second;
}

void Sommets::SetIndiceDegre(float indice) // indice normalise
{
    m_indices[0].second = indice;
}

void Sommets::SetIndiceVectorNN(float indice) // indice non normalise
{
    m_indices[1].first = indice;
}

float Sommets::GetIndiceVectorNN() const // indice non normalise
{
    return m_indices[1].first;
}

float Sommets::GetIndiceVector() const// indice normalise
{
    return m_indices[1].second;
}

void Sommets::SetIndiceVector(float indice) // indice normalise
{
    m_indices[1].second = indice;
}

void Sommets::SetIndiceProximiteNN(float indice) // indice non normalise
{
    m_indices[2].first = indice;
}

float Sommets::GetIndiceProximiteNN() const// indice non normalise
{
    return m_indices[2].first;
}

float Sommets::GetIndiceProximite() const// indice normalise
{
    return m_indices[2].second;
}

void Sommets::SetIndiceProximite(float indice) // indice normalise
{
   m_indices[2].second = indice;
}

void Sommets::SetIndiceIntermediaireNN(float indice) // indice non normalise
{
    m_indices[3].first = indice;
}

float Sommets::GetIndiceIntermediaireNN() const// indice non normalise
{
    return m_indices[3].first;
}

float Sommets::GetIndiceIntermediaire() const// indice normalise
{
    return m_indices[3].second;
}

void Sommets::SetIndiceIntermediaire(float indice) // indice normalise
{
    m_indices[3].second = indice;
}
>>>>>>> Stashed changes
