#include "Graphe.h"
#include "Sommets.h"
#include "Aretes.h"
#include <vector>
#include <cmath>
#include <fstream>

Graphe::Graphe()
{

}
Graphe::Graphe(std::string nomFichier)
{
    m_pondere=false;
    int num,x,y,j,k;
    char nom;
    std::ifstream ifs{nomFichier};
    if(!ifs)
    {
        std::cout<<"erreur ouverture fichier";
        exit(0);
    }
    ifs>>m_orient;
    ifs>>m_ordre;
    for(int i=0; i<m_ordre;++i)
    {
        ifs>>num;
        ifs>>nom;
        ifs>>x;
        ifs>>y;
        m_sommets.push_back(new Sommets(num,nom, x, y));
    }
    ifs>>m_taille;
        for(int i=0; i<m_taille; ++i)
        {
            ifs>>num;
            ifs>>j;
            ifs>>k;
            m_aretes.push_back(new Aretes(num, m_sommets[j],m_sommets[k]));
            m_sommets[j]->ajouterSucc(m_sommets[k]);
            if(m_orient == 0 )
                m_sommets[k]->ajouterSucc(m_sommets[j]);
        }
}
void Graphe::ponderation(std::string fich)
{
    int taile, a,b;
    std::ifstream ifs{fich};
    if(!ifs)
    {
        std::cout<<"erreur fichier";
        return;
    }
    ifs>>taile;
    for(int i=0; i<taile;++i)
    {
        ifs>>a;
        ifs>>b;
        m_aretes[a]->SetPoids(b);
    }
    m_pondere=true;
}

void Graphe::afficher()
{
    Svgfile svgout;
    svgout.addGrid();

    std::cout << m_orient << std::endl;
    std::cout << m_ordre << std::endl;
    for(int i=0; i<m_ordre; i++)
    {
        m_sommets[i]->afficherSommet();
        svgout.addCross(100*m_sommets[i]->GetX(), 100*m_sommets[i]->GetY(), 5, "red");
        svgout.addText(100*m_sommets[i]->GetX(), 100*m_sommets[i]->GetY()-15, m_sommets[i]->GetName(), "blue");
    }
    std::cout << m_taille << std::endl;
    for(int i=0; i<m_taille; i++)
    {
        m_aretes[i]->afficherArete(m_pondere);
        svgout.addLine(100*m_aretes[i]->GetSommet1()->GetX(), 100*m_aretes[i]->GetSommet1()->GetY(), 100*m_aretes[i]->GetSommet2()->GetX(), 100*m_aretes[i]->GetSommet2()->GetY(), "blue");
        if(m_pondere)
            svgout.addText((m_aretes[i]->GetSommet1()->GetX()+m_aretes[i]->GetSommet2()->GetX())*50, (m_aretes[i]->GetSommet1()->GetY()+m_aretes[i]->GetSommet2()->GetY())*50, m_aretes[i]->GetPoids(), "orange");
    }
}


void Graphe::supprimerArete()
{
    int n ;
    std::cout << "Saisir l'indice de l'arete que vous voulez supprimer" << std::endl ;
    std::cin >> n ;
    m_aretes.erase(m_aretes.begin()+n) ;
    m_taille -= 1 ;
    for(size_t i=n ; i<m_aretes.size() ; ++i) { m_aretes[i]->SetNum(m_aretes[i]->GetNum()-1) ; }
}


/// CENTRALITE DE DEGRE

void Graphe::centraliteDegre()
{
    for(int i=0; i<m_taille; i++)
    {
        m_aretes[i]->GetSommet1()->SetIndiceDegreNN(m_aretes[i]->GetSommet1()->GetIndiceDegreNN()+1);
        if(m_orient == false)
            m_aretes[i]->GetSommet2()->SetIndiceDegreNN(m_aretes[i]->GetSommet2()->GetIndiceDegreNN()+1);
    }
    ///affcichage des r�sultats
    std::cout << "\n\t**Indice de centralite de degre**\n"<<std::endl;
    for(int i=0; i<m_ordre; i++)
    {
        m_sommets[i]->SetIndiceDegre(m_sommets[i]->GetIndiceDegreNN()/(m_ordre-1));
        std::cout << "Sommet "<<m_sommets[i]->GetName()<<" : \tnon normalise : "<< m_sommets[i]->GetIndiceDegreNN()<<" \t\tnormalise : " << m_sommets[i]->GetIndiceDegre()<< std::endl;
    }

    ///sauvegarde des r�sultats
    std::ofstream ofs{"ResultatCentraliteDegre.txt"};
    if(!ofs)
    {
        std::cout<<"pbm ouverture fichier degre";
        exit(0);
    }
    for(auto a:m_sommets)
        ofs<<"Sommet "<<a->GetNum()<<" : "<<a->GetIndiceDegreNN()<<"\t"<<a->GetIndiceDegre()<<std::endl;

}

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

        /* S�lectionner et marquer le sommet s non marqu� ayant la plus petite distance
        au sommet initial s0 */
        double d=999 ;
        int n=0 ; //Va correspondre � l'indice du sommet avec la plus petite distance � s0

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
        //Pour chaque successeur non marqu� x de s :
        for(size_t i=0; i<succ.size(); ++i)
        {
            if(marquages[succ[i]->GetNum()]==0)
            {
                /* si en passant par s le chemin est plus court, on met � jour
                la distance et on note que s est le pr�d�cesseur de x*/
                if((d+obtenirPoid(s,succ[i]))<=distances[succ[i]->GetNum()])
                {

                    distances[succ[i]->GetNum()]=d+obtenirPoid(s,succ[i]) ;
                }
            }
        }
    }
    return distances[numF] ;
}

void Graphe::centraliteDeProxUnSommet(size_t num_s0, Sommets* Actuel)
{
    double cProx = 0;
    for(size_t i=0 ; i< m_sommets.size(); ++i)
    {
        if(m_sommets[i]->GetNum() != (int)num_s0)
        {
            cProx = cProx + dijkstra(num_s0,(size_t)(m_sommets[i]->GetNum())) ;
        }
    }
    ///affichage des resultats
    if ( cProx ==0 )//
    {
        Actuel->SetIndiceProximiteNN(0);
        Actuel->SetIndiceProximite(0);
        std::cout << std::endl <<  num_s0 << " : "<<Actuel->GetIndiceProximiteNN();
    }
    else{
        Actuel->SetIndiceProximiteNN(1/cProx);
        Actuel->SetIndiceProximite((m_ordre-1)/cProx);
        std::cout << std::endl << num_s0 << " : "<<  1/cProx <<"\t\t"<<  (m_ordre-1)/cProx ;
    }
}

void Graphe::centraliteDeProxSommets()
{
    std::cout << "\n\t**Centralite de Proximite** " ;
    for(auto a:m_sommets)
       centraliteDeProxUnSommet((size_t)(a->GetNum()), a);

    ///sauvegarde des r�sultats
    std::ofstream ofs{"ResultatCentraliteDeProximite.txt"};
    if(!ofs)
    {
        std::cout<<"pbm ouverture fichier prox";
        exit(0);
    }
    for(auto a:m_sommets)
        ofs<<"Sommet "<<a->GetNum()<<" : "<<a->GetIndiceProximiteNN()<<"\t"<<a->GetIndiceProximite()<<std::endl;
}
///Centralit� de vecteur propre

void Graphe::VecteurPropre()
{
    for(auto a:m_sommets)
        a->SetIndiceVectorNN(1);

    std::vector<float> adj;//vecteur r�cup�rant la valeur das sommets adjacents
    float sommeadj=0.0, lambda=0.0, plambda=0.0;
    do
    {
        adj.clear();//pour que ca reprenne a 0 a chaque tour de boucle
        adj.resize(m_ordre);
        sommeadj=0.0;
        for(int i=0; i<m_ordre; ++i)//on r�cup�re la valeure des sommets adjacents pour chaque sommet
            for(auto a:m_aretes)
                if(a->GetSommet1()==m_sommets[i] || a->GetSommet2()==m_sommets[i])
                    adj[i]+=m_sommets[i]->GetIndiceVectorNN();

        for(auto a: adj)//on additionne leurs carr�s
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

    ///affichage des r�sultats
    std::cout<<"\t**Centralite de vecteur propre**\n\n";
    for(auto a : m_sommets)
        std::cout << "Sommet " << a->GetName() << " : \tnon normalise : " << a->GetIndiceVectorNN()<<" \t\tnormalise : "<<a->GetIndiceVector()<<std::endl;

    ///sauvegarde des r�sultats
    std::ofstream ofs{"ResultatCentraliteVecteurPropre.txt"};
    if(!ofs)
    {
        std::cout<<"pbm ouverture fichier vecteur";
        exit(0);
    }
    for(auto a:m_sommets)
        ofs<<"Sommet "<< a->GetName()<<" : "<<a->GetIndiceVectorNN()<<"\t"<<a->GetIndiceVector()<<std::endl;

}

///centralite d'intermediarit�
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

///affichage des r�sultats
    std::cout << "\n\t **Centralite d'Intermediarite**\n";
    for(int i = 0; i<m_ordre; i++)
    {
        m_sommets[i]->SetIndiceIntermediaireNN(m_sommets[i]->GetIndiceIntermediaireNN()/ncc);
        m_sommets[i]->SetIndiceIntermediaire((2*m_sommets[i]->GetIndiceIntermediaireNN())/(pow(m_ordre, 2)-3*m_ordre+2));
        std::cout << "Sommet " << m_sommets[i]->GetNum() << " : "<< "\tnon normalise : " << m_sommets[i]->GetIndiceIntermediaireNN() << "\t\tnormalise : " << m_sommets[i]->GetIndiceIntermediaire()<<std::endl;
    }
///sauvegarde des r�sultats
    std::ofstream ofs{"ResultatCentraliteD'Intermediarite.txt"};
    if(!ofs)
    {
        std::cout<<"pbm ouverture fichier intermediarite";
        exit(0);
    }
    for(auto a:m_sommets)
        ofs<<"Sommet "<<a->GetNum()<<" : "<<a->GetIndiceIntermediaireNN()<<"\t"<<a->GetIndiceIntermediaire()<<std::endl;

}


 Graphe Graphe::operator=(Graphe const&b)
{
    Graphe a;
    a.m_pondere=b.m_pondere;
    a.m_orient=b.m_orient;
    a.m_ordre=b.m_ordre;
    a.m_taille=b.m_taille;
    a.m_sommets.clear();
    a.m_aretes.clear();
    for(int i=0; i<a.m_ordre; ++i)
        a.m_sommets.push_back(b.m_sommets[i]);
    for(int i=0; i<a.m_taille; ++i)
        a.m_aretes.push_back(b.m_aretes[i]);
    return a;
}
