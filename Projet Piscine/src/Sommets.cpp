#include "Sommets.h"
#include "svgfile.h"

Sommets::Sommets(int num,char nom,int x, int y) : m_x{x}, m_y{y}, m_num{num}, m_indice_degre_NN{0}, m_indice_degre{0}, m_indice_vector_NN{0}, m_indice_vector{0}, m_indice_proximite_NN{0}, m_indice_proximite{0}, m_indice_intermediaire_NN{0}, m_indice_intermediaire{0}, m_name{nom}
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
    m_indice_degre_NN = indice;
}

float Sommets::GetIndiceDegreNN() const// indice non normalise
{
    return m_indice_degre_NN;
}

float Sommets::GetIndiceDegre() const // indice normalise
{
    return m_indice_degre;
}

void Sommets::SetIndiceDegre(float indice) // indice normalise
{
    m_indice_degre = indice;
}

void Sommets::SetIndiceVectorNN(float indice) // indice non normalise
{
    m_indice_vector_NN = indice;
}

float Sommets::GetIndiceVectorNN() const // indice non normalise
{
    return m_indice_vector_NN;
}

float Sommets::GetIndiceVector() const// indice normalise
{
    return m_indice_vector;
}

void Sommets::SetIndiceVector(float indice) // indice normalise
{
    m_indice_vector = indice;
}

void Sommets::SetIndiceProximiteNN(float indice) // indice non normalise
{
    m_indice_proximite_NN = indice;
}

float Sommets::GetIndiceProximiteNN() const// indice non normalise
{
    return m_indice_proximite_NN;
}

float Sommets::GetIndiceProximite() const// indice normalise
{
    return m_indice_proximite;
}

void Sommets::SetIndiceProximite(float indice) // indice normalise
{
    m_indice_proximite = indice;
}

void Sommets::SetIndiceIntermediaireNN(float indice) // indice non normalise
{
    m_indice_intermediaire_NN = indice;
}

float Sommets::GetIndiceIntermediaireNN() const// indice non normalise
{
    return m_indice_intermediaire_NN;
}

float Sommets::GetIndiceIntermediaire() const// indice normalise
{
    return m_indice_intermediaire;
}

void Sommets::SetIndiceIntermediaire(float indice) // indice normalise
{
    m_indice_intermediaire = indice;
}
