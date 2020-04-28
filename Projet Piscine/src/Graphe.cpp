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
<<<<<<< Updated upstream
=======

void Graphe::centraliteDegre()
{
    for(int i=0; i<m_taille; i++)
    {
        m_aretes[i]->GetSommet1()->SetIndiceNN(m_aretes[i]->GetSommet1()->GetIndiceNN()+1);
        if(m_orient == false)
            m_aretes[i]->GetSommet2()->SetIndiceNN(m_aretes[i]->GetSommet2()->GetIndiceNN()+1);
    }
    std::cout << "\nIndice de centralite de degre : \n"<<std::endl;
    for(int i=0; i<m_ordre; i++)
    {
        m_sommets[i]->SetIndice(m_sommets[i]->GetIndiceNN()/(m_ordre-1));
        std::cout << "Sommet "<<m_sommets[i]->GetName()<<" : \tnon normalise : "<< m_sommets[i]->GetIndiceNN()<<" \tnormalise : " << m_sommets[i]->GetIndice()<< std::endl;
    }

}
<<<<<<< Updated upstream
>>>>>>> Stashed changes
=======

/// CENTRALITE DE PROXIMITE

bool encoreMarquage(std::vector<int> marquages)
{
    bool b = false ;
    for(size_t i=0; i<marquages.size(); ++i)
        if(marquages[i]==0)
            b = true;

    return b ;
}

double Graphe::obtenirPoid(const Sommets* som1, const Sommets* som2)
{
    double r=0 ;
    for(size_t i=0 ; i< m_aretes.size() ; ++i)
        if((som1 == m_aretes[i]->GetSommet1() )&&(som2 == m_aretes[i]->GetSommet2()))
            r = m_aretes[i]->GetPoids() ;

    return r ;
}

double Graphe::dijkstra(size_t num_s0, size_t numF)
{
    std::vector<int> marquages((int)m_sommets.size(),0) ;
    std::vector<double> distances((double)m_sommets.size(),999) ;

    distances[num_s0]=0;
    std::vector<const Sommets*> succ ;
    std::vector<int> poid ;
    const Sommets* s ;

    //Tant qu'il y a des sommets non marquer on reste dans la boucle
    while(encoreMarquage(marquages)==true)
    {

        /* Sélectionner et marquer le sommet s non marqué ayant la plus petite distance
        au sommet initial s0 */
        double d=999 ;
        int n=0 ; //Va correspondre à l'indice du sommet avec la plus petite distance à s0

        for(size_t i=0; i<m_sommets.size() ; ++i)
            if(marquages[i]==0)
                if(distances[i]<d)
                {
                    d=distances[i] ;
                    n=i ;
                }

        marquages[n]=1;
        s=m_sommets[n];
        succ=*s->getSuccesseurs();
        //Pour chaque successeur non marqué x de s :
        for(size_t i=0; i<succ.size(); ++i)
        {
            if(marquages[succ[i]->GetNum()]==0)
            {
                /* si en passant par s le chemin est plus court, on met à jour
                la distance et on note que s est le prédécesseur de x*/
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
        if(m_sommets[i]->GetNum() != (int)num_s0)
        {
            cProx = cProx + dijkstra(num_s0,(size_t)(m_sommets[i]->GetNum())) ;

        }
    }
    if ( cProx ==0 )
    {
        std::cout << std::endl <<  num_s0 << " : "<< "Pas d'indice" << std::endl ;
    }
    else{
        std::cout << std::endl << num_s0 << " : "<<  1/cProx << "     " <<  (m_ordre-1)/cProx ;
    }

}

void Graphe::centraliteDeProxSommets()
{
    std::cout << "\n\t**Centralite de Proximite** " ;
    for(size_t i=0 ; i< m_sommets.size(); ++i)
    {
       centraliteDeProxUnSommet((size_t)(m_sommets[i]->GetNum())) ;
    }

}

///Centralité de vecteur propre

void Graphe::VecteurPropre()
{
    for(auto a:m_sommets)
        a->SetIndiceVectorNN(1);

    std::vector<float> adj;//vecteur récupérant la valeur das sommets adjacents
    float sommeadj=0.0, lambda=0.0, plambda=0.0;
    do
    {
        adj.clear();//pour que ca reprenne a 0 a chaque tour de boucle
        adj.resize(m_ordre);
        sommeadj=0.0;
        for(int i=0; i<m_ordre; ++i)//on récupère la valeure des sommets adjacents pour chaque sommet
            for(auto a:m_aretes)
                if(a->GetSommet1()==m_sommets[i] || a->GetSommet2()==m_sommets[i])
                    adj[i]+=m_sommets[i]->GetIndiceVectorNN();

        for(auto a: adj)//on additionne leurs carrés
            sommeadj+=pow(a,2);

        plambda=lambda;//mmr

        if(plambda==0)//pour ne pas diviser par 0
            plambda=1;

        lambda=sqrt(sommeadj);

        for(int i=0; i<m_ordre; ++i)//on donne la nouvelle valeure aux indices de chaques sommets
            m_sommets[i]->SetIndiceVectorNN( adj[i]/lambda);

    }while(lambda/plambda>1.5);//lambda/plambda => variations de lambda

    for(auto a:m_sommets)//normalise les indices
        a->SetIndiceVector(a->GetIndiceVectorNN()/(m_ordre-1));

    std::cout<<"\t**Centralite de vecteur propre**\n\n";
    for(auto a : m_sommets)
        std::cout << "Sommet " << a->GetName() << " : \tnon normalise : " << a->GetIndiceVectorNN()<<" \tnormalise : "<<a->GetIndiceVector()<<std::endl;

    adj.erase(adj.begin(), adj.end());
}



void Graphe::Intermediarite()
{
    int ncc = 0;
    for(int i=0; i<m_ordre; ++i)
        for(int j=0; i<m_ordre; ++i)
            if(j!=i)
                for(int k=j+1; k<m_ordre;++k)
                    if(k!=i)
                    {
                        ncc++;
                        if( dijkstra(m_sommets[j]->GetNum(),m_sommets[i]->GetNum())+dijkstra(m_sommets[i]->GetNum(),m_sommets[k]->GetNum())==dijkstra(m_sommets[j]->GetNum(),m_sommets[k]->GetNum()))
                            m_sommets[i]->SetIndiceIntermediaireNN(m_sommets[i]->GetIndiceIntermediaireNN()+1);

                    }

    std::cout << "\n\t **Centralite d'Intermediarite**\n";
    for(int i = 0; i<m_ordre; i++)
    {
        m_sommets[i]->SetIndiceIntermediaireNN(m_sommets[i]->GetIndiceIntermediaireNN()/ncc);
        m_sommets[i]->SetIndiceIntermediaire((2*m_sommets[i]->GetIndiceIntermediaireNN())/(pow(m_ordre, 2)-3*m_ordre+2));
        std::cout << "Sommet " << m_sommets[i]->GetNum() << " : "<< "\tnon normalise : " << m_sommets[i]->GetIndiceIntermediaireNN() << "\t\tnormalise : " << m_sommets[i]->GetIndiceIntermediaire()<<std::endl;
    }
}

>>>>>>> Stashed changes
