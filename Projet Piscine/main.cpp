#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>
#include "sauvegarde.h"
#include "Graphe.h"
#include "svgfile.h"

int main()
{
    Graphe a=charger();
    a.VecteurPropre();

    a.centraliteDeProxSommets();

    return 0;
}
