#include "Graphe.h"
#include "Sommets.h"
#include "Aretes.h"

Graphe::Graphe(std::string nomFichier, bool ponderation)
{
    std::ifstream ifs{nomFichier};
    if (!ifs)
        throw std::runtime_error( "Impossible d'ouvrir en lecture " + nomFichier );

    ifs >> m_orient;
    if ( ifs.fail() )
        throw std::runtime_error("Probleme lecture oriente ou non");

    ifs >> m_ordre; // lecture du nombre de sommets dans le graphe
    if ( ifs.fail() )
        throw std::runtime_error("Probleme lecture ordre du graphe");
    std::string name;
    int temp, temp1, temp2;
    for (int i=0; i<m_ordre; ++i)
    {
        m_sommets.push_back( new Sommets{i} );
        ifs >> temp >> name >> temp1 >> temp2;
        m_sommets[temp]->SetName(name);
        m_sommets[temp]->SetX(temp1);
        m_sommets[temp]->SetY(temp2);
    }

    ifs >> m_taille; // lecture du nombre darête
    if ( ifs.fail() )
        throw std::runtime_error("Probleme lecture taille du graphe");
    for (int i=0; i<m_taille; i++)
    {
        m_aretes.push_back( new Aretes{i} );
        ifs >> temp >> temp1 >> temp2;
        m_aretes[temp]->SetSommet1(m_sommets[temp1]);
        m_aretes[temp]->SetSommet2(m_sommets[temp2]);
    }
    if(ponderation == true)
    {
        std::ifstream ofs{"arete.txt"};
        if (!ofs)
            throw std::runtime_error( "Impossible d'ouvrir en lecture arete.txt");

        ofs >> m_taille; // lecture du nombre darête
        if ( ofs.fail() )
            throw std::runtime_error("Probleme lecture taille du graphe");

        double temp3;
        for(int i=0; i<m_taille; i++)
        {
            ofs >> temp >> temp3;
            m_aretes[temp]->SetPoids(temp3);
        }
    }
}

void Graphe::afficher(bool ponderation)
{
    Svgfile svgout;
    svgout.addGrid();

    std::cout << m_orient << std::endl;
    std::cout << m_ordre << std::endl;
    for(int i=0; i<m_ordre; i++)
    {
        m_sommets[i]->afficherSommet();
        svgout.addCross(m_sommets[i]->GetX(), m_sommets[i]->GetY(), 5, "red");
        svgout.addText(m_sommets[i]->GetX(), m_sommets[i]->GetY()-15, m_sommets[i]->GetName(), "blue");
    }
    std::cout << m_taille << std::endl;
    for(int i=0; i<m_taille; i++)
    {
        m_aretes[i]->afficherArete(ponderation);
        svgout.addLine(m_aretes[i]->GetSommet1()->GetX(), m_aretes[i]->GetSommet1()->GetY(), m_aretes[i]->GetSommet2()->GetX(), m_aretes[i]->GetSommet2()->GetY(), "blue");

        if(ponderation == true)
        {
            svgout.addText((m_aretes[i]->GetSommet1()->GetX()-m_aretes[i]->GetSommet2()->GetX())/2, (m_aretes[i]->GetSommet1()->GetY()-m_aretes[i]->GetSommet2()->GetY())/2, m_aretes[i]->GetPoids(), "blue");
        }
    }

}
