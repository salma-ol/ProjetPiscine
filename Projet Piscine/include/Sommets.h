#ifndef SOMMETS_H
#define SOMMETS_H
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>
#include "svgfile.h"

class Sommets
{
    public:
        Sommets(int,char,int,int);
        ~Sommets();

        const int GetX() const;
        const int GetY() const;
        const int GetNum() const ;
        const std::string GetName() const ;

        float GetIndiceDegreNN() const;
        float GetIndiceDegre()const;
        float GetIndiceVectorNN()const;
        float GetIndiceVector()const;
        float GetIndiceProximiteNN()const;
        float GetIndiceProximite()const;
        float GetIndiceIntermediaireNN()const;
        float GetIndiceIntermediaire()const;

        void SetX(int x);
        void SetY(int y);
        void SetName(std::string name);
        void SetIndiceDegreNN(float indice);
        void SetIndiceDegre(float indice);
        void SetIndiceVectorNN(float indice);
        void SetIndiceVector(float indice);
        void SetIndiceProximiteNN(float indice);
        void SetIndiceProximite(float indice);
        void SetIndiceIntermediaireNN(float indice);
        void SetIndiceIntermediaire(float indice);
        void afficherSommet();
        const std::vector<const Sommets*>* getSuccesseurs() const ;
        void ajouterSucc(const Sommets* s);
        void SetNum(int num) ;
        void SetSucceseurs(std::vector<const Sommets*> succ) ;

    private:
        int m_x;
        int m_y;
        int m_num;
        std::vector<std::pair<float,float>> m_indices;
        //0->degre
        //1->veteur
        //2->proximité
        //3->intermediare
        //firdt->non normalisé, second->normalisé
        std::string m_name;
        std::vector<const Sommets*> m_successeurs ;
};

#endif // SOMMETS_H
