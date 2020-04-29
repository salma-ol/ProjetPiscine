#include "Graphe.h"
#include "Sommets.h"
#include "Aretes.h"
#include <vector>
#include <cmath>
#include <fstream>
#include <queue>

Graphe::Graphe(std::string nomFichier)
{
    m_pondere=false;
    int num,x,y,j,k;
    char nom;
    std::ifstream ifs{nomFichier};
    if(!ifs)
    {
        std::cout<<"erreur ouverture fichier";
        return;
    }
    ifs>>m_orient;
    ifs>>m_ordre;
    for(int i=0; i<m_ordre; ++i)
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
        {
            m_sommets[k]->ajouterSucc(m_sommets[j]);
        }
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
    for(int i=0; i<taile; ++i)
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
            svgout.addText((m_aretes[i]->GetSommet1()->GetX()+m_aretes[i]->GetSommet2()->GetX())/2, (m_aretes[i]->GetSommet1()->GetY()+m_aretes[i]->GetSommet2()->GetY())/2, m_aretes[i]->GetPoids(), "orange");
    }
}


void Graphe::supprimerArete()
{
    int n ;
    std::cout << "Saisir l'indice de l'arete que vous voulez supprimer" << std::endl ;
    std::cin >> n ;

    m_taille -= 1 ;

    ///supression au niveau des succeseur :
    const Sommets* s = m_sommets[(m_aretes[n]->GetSommet1())->GetNum()] ;
    std::vector<const Sommets*> succ = *s->getSuccesseurs();

    for(size_t j=0 ; j< succ.size() ; ++j)
    {
        if( (succ[j]->GetNum() == (m_aretes[n]->GetSommet2())->GetNum()) )
        {
            succ.erase(succ.begin() + j) ;
            //std::cout << m_sommets[(m_aretes[n]->GetSommet1())->GetNum()]->GetNum() << "  " << succ[j]->GetNum()  ;
            //std::cout << "  taille :" << succ.size() << std::endl ;
        }
    }
    m_sommets[(m_aretes[n]->GetSommet1())->GetNum()]->SetSucceseurs(succ) ;
    if(m_orient==0)
    {
        const Sommets* s = m_sommets[(m_aretes[n]->GetSommet2())->GetNum()] ;
        std::vector<const Sommets*> succ = *s->getSuccesseurs();
        for(size_t j=0 ; j< succ.size() ; ++j)
        {
            if( (succ[j]->GetNum() == (m_aretes[n]->GetSommet1())->GetNum()) )
            {
                succ.erase(succ.begin() + j) ;
                //std::cout << m_sommets[(m_aretes[n]->GetSommet2())->GetNum()]->GetNum() << "  " << succ[j]->GetNum()  ;
                //std::cout << "taille :" << succ.size() << std::endl ;
            }
        }
        m_sommets[(m_aretes[n]->GetSommet2())->GetNum()]->SetSucceseurs(succ) ;
    }
    m_aretes.erase(m_aretes.begin()+n) ;

    for(size_t i=n ; i<m_aretes.size() ; ++i)
    {
        m_aretes[i]->SetNum(m_aretes[i]->GetNum()-1) ;
    }
    /* Verification for(size_t j=0 ; j<m_sommets.size() ; ++j)
    {
    std::cout << "successeur : " ;
    succ = (*m_sommets[j]->getSuccesseurs()) ;
    for(size_t i=0 ; i< succ.size() ; ++i)
    {
        std::cout<< succ[i]->GetNum() ;
    }
    } */
    rechercher_afficher_CC() ;
    afficher() ;
}

void Graphe::supprimerAretes()
{
    int n =0 ;
    do{
        supprimerArete() ;
        std::cout << "Si vous ne voulez plus supprimer d'aretes taper -1 sinon 0"  ;
        std::cin>>n ;
    }while(n!=-1) ;
}

/// Recherche composante connexe

std::vector<int> Graphe::BFS(int num_s0)const
{
    /// d�claration de la file
    std::queue<int> file ;
    /// pour le marquage
    //vect avec m_sommets.size() elements tous initialis� � 0
    //0 --> non decouvert (B) 1--> decouvert (G)
    std::vector<int> couleurs((int)m_sommets.size(),0);
    ///pour noter les pr�d�cesseurs : on note les num�ros des pr�d�cesseurs (on pourrait stocker des pointeurs sur ...)
    //vect avec m_sommets.size() elements tous initialis� � -1
    std::vector<int> preds((int)m_sommets.size(),-1);
    ///�tape initiale : on enfile et on marque le sommet initial
    file.push(num_s0) ;
    couleurs[num_s0] = 1 ;

    const Sommets* s;
    ///tant que la file n'est pas vide
    while(!file.empty())
    {
        // s corresponds au 1er de la file (donc celui qui va etre defile)
        s = m_sommets[file.front()] ;
        ///on d�file le prochain sommet
        file.pop() ;
        ///pour chaque successeur du sommet d�fil�
        for(auto succ:(*s->getSuccesseurs()))
        {
            ///s'il n'est pas marqu�
            if(couleurs[succ->GetNum()] == 0)
            {
                ///on le marque
                couleurs[succ->GetNum()] = 1 ;
                ///on note son pr�decesseur (=le sommet d�fil�)
                preds[succ->GetNum()] = s->GetNum() ;
                ///on le met dans la file
                file.push(succ->GetNum()) ;
            }
        }
    }
    return preds;
}

void Graphe::rechercher_afficher_CC()
{
    size_t num=0;
    bool test;
    int ncc=0;
    ///pour noter les num�ros de CC
    std::vector<int> cc(m_sommets.size(),-1);
    do
    {
        int nbImpair=0 ;
        cc[num]=num;
        std::cout<<std::endl<<"composante connexe "<<ncc<<" : "<<num<<" ";
        ncc++;
        //Determination de degre du sommet[num]
        if( ((*m_sommets[num]->getSuccesseurs()).size())%2 != 0)
        {
            nbImpair++ ;
        }

        ///lancement d'un BFS sur le sommet num
        std::vector<int> arbre_BFS=BFS(num);
        ///affichage des sommets decouverts lors du parcours (ceux qui ont un predecesseur
        for(size_t i=0; i<arbre_BFS.size(); ++i)
        {
            if ((i!=num)&&(arbre_BFS[i]!=-1))
            {
                cc[i]=num;
                std::cout<<i<<" ";
                //Determination si cc[i] a un nbre paire ou imparire de succeseur
                if( ((*m_sommets[i]->getSuccesseurs()).size())%2 != 0)
                {
                    nbImpair++ ;
                }
            }
        }
        /*if(nbImpair==2){
                std::cout<< " --> La cc " << num << " est une chaine eulerienne" <<std::endl ;
        }else if(nbImpair==0){
            std::cout<< " --> La cc " << num << " est un cycle eulerien" <<std::endl ;
        }else{
            std::cout<< " --> La cc " << num << " n'est ni un cycle eulerien ni une chaine eulerienne " <<std::endl ;}*/
        ///recherche d'un sommet non explor�
        ///pour relancer un BFS au prochain tour
        test=false;
        for(size_t i=0; i<m_sommets.size(); ++i)
        {
            if (cc[i]==-1)
            {
                num=i;
                test=true;
                break;
            }
        }
    }
    while(test==true);
    std::cout<<std::endl;
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
        std::cout << "Sommet "<<m_sommets[i]->GetName()<<" : \tnon normalise : "<< m_sommets[i]->GetIndiceDegreNN()<<" \tnormalise : " << m_sommets[i]->GetIndiceDegre()<< std::endl;
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
    if ( cProx ==0 )
    {
        Actuel->SetIndiceProximiteNN(0);
        std::cout << std::endl <<  num_s0 << " : "<< "Pas d'indice" << std::endl ;
    }
    else
    {
        Actuel->SetIndiceProximiteNN(1/cProx);
        Actuel->SetIndiceProximite((m_ordre-1)/cProx);
        std::cout << std::endl << num_s0 << " : "<<  1/cProx << "     " <<  (m_ordre-1)/cProx ;
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

    }
    while(lambda/plambda>1.5); //lambda/plambda => variations de lambda

    for(auto a:m_sommets)//normalise les indices
        a->SetIndiceVector(a->GetIndiceVectorNN()/(m_ordre-1));

    ///affichage des r�sultats
    std::cout<<"\t**Centralite de vecteur propre**\n\n";
    for(auto a : m_sommets)
        std::cout << "Sommet " << a->GetName() << " : \tnon normalise : " << a->GetIndiceVectorNN()<<" \tnormalise : "<<a->GetIndiceVector()<<std::endl;

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
                for(int k=j+1; k<m_ordre; ++k)
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
