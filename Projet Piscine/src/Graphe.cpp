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

    ifs >> m_taille; // lecture du nombre dar�te
    if ( ifs.fail() )
        throw std::runtime_error("Probleme lecture taille du graphe");
    for (int i=0; i<m_taille; i++)
    {
        m_aretes.push_back( new Aretes{i} );
        ifs >> temp >> temp1 >> temp2;
        m_aretes[temp]->SetSommet1(m_sommets[temp1]);
        m_aretes[temp]->SetSommet2(m_sommets[temp2]);
        ///Successeur
        m_sommets[temp1]->ajouterSucc(m_sommets[temp2]);
        if(m_orient == 0 )
        {
            m_sommets[temp2]->ajouterSucc(m_sommets[temp1]);
        }
    }

if(ponderation == true)
{
    std::ifstream ofs{"arete.txt"};
    if (!ofs)
        throw std::runtime_error( "Impossible d'ouvrir en lecture arete.txt");

    ofs >> m_taille; // lecture du nombre dar�te
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

    centraliteDeProxSommets() ;

}


/// CENTRALITE DE PROXIMITE

bool encoreMarquage(std::vector<int> marquages)
{
    bool b = false ;
    for(size_t i=0; i<marquages.size(); ++i)
    {
        if(marquages[i]==0)
        {
            b = true;
        }
    }
    return b ;
}

double Graphe::obtenirPoid(const Sommets* som1, const Sommets* som2)
{
    double r=0 ;
    for(size_t i=0 ; i< m_aretes.size() ; ++i)
    {
        if((som1 == m_aretes[i]->GetSommet1() )&&(som2 == m_aretes[i]->GetSommet2()))
        {

            r = m_aretes[i]->GetPoids() ;

        }
    }
    return r ;
}

double Graphe::dijkirsta(size_t num_s0, size_t numF)
{
    std::vector<int> marquages((int)m_sommets.size(),0) ;
    std::vector<double> distances((double)m_sommets.size(),999) ;

    distances[num_s0]=0 ;
    std::vector<const Sommets*> succ ;
    std::vector<int> poid ;
    const Sommets* s ;

    //Tant qu'il y a des sommets non marquer on reste dans la boucle
    while(encoreMarquage(marquages)==true)
    {
        /* S�lectionner et marquer le sommet s non marqu� ayant la plus petite distance
        au sommet initial s0 */
        double d=999 ;
        int n=0 ; //Va correspondre � l'indice du sommet avec la plus petite distance � s0

        for(size_t i=0; i<m_sommets.size() ; ++i)
        {
            if(marquages[i]==0)
            {
                if(distances[i]<d)
                {
                    d=distances[i] ;
                    n=i ;
                }
            }
        }
        marquages[n]=1 ;
        s=m_sommets[n] ;
        succ=s->getSuccesseurs() ;
        //Pour chaque successeur non marqu� x de s :
        for(size_t i=0; i<succ.size(); ++i)
        {
            if(marquages[succ[i]->GetNum()]==0)
            {

                /* si en passant par s le chemin est plus court, on met � jour
                la distance et on note que s est le pr�d�cesseur de x*/
                if((d+obtenirPoid(s,succ[i]))<distances[succ[i]->GetNum()])
                {
                    distances[succ[i]->GetNum()]=d+obtenirPoid(s,succ[i]) ;
                }
            }
        }
    }
    return distances[numF] ;
}

void Graphe::centraliteDeProxUnSommet(size_t num_s0)
{
    double cProx = 0;
    for(size_t i=0 ; i< m_sommets.size(); ++i)
    {
        if(m_sommets[i]->GetNum() != num_s0)
        {
            cProx = cProx + dijkirsta(num_s0,(size_t)(m_sommets[i]->GetNum())) ;

        }

    }
    if ( cProx ==0 )
    {
        std::cout << std::endl <<  num_s0 << " : "<< "Pas d'indice" << std::endl ;
    }
    else{
        std::cout << std::endl << num_s0 << " : "<<  1/cProx << "     " <<  m_ordre/cProx ;
    }

    // return (m_ordre/cProx) ;
}

void Graphe::centraliteDeProxSommets()
{
    std::cout << "   **Centralite de Proximite** " ;
    for(size_t i=0 ; i< m_sommets.size(); ++i)
    {
       centraliteDeProxUnSommet((size_t)(m_sommets[i]->GetNum())) ;
    }

}

