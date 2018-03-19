#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
#include <sstream>
#include <cstdlib>
#include <algorithm>

#include "calculation.h"
#include "topology.h"
#include "routing.h"

using namespace std;

Calculation::Calculation() {}

Calculation::~Calculation() {}

/**
 * Constructeur qui charge les informations 
 * de la topologie et table de routage en mémoire.
 */
Calculation::Calculation(char* topoFile, char* routeFile) 
{
	topologyTable.loadData(topoFile);
	routingTable.loadData(routeFile);
}

/**
 * Méthode qui calcule le nombre de sauts 
 * d'un noeud source jusqu'au noeud destination.
 * n’oubliez pas de compléter le code !
 */
int Calculation::getHopCount(int fromId, int toId)
{
	int count = 0;
	bool ok;
	
	struct hostNode * fromHost = topologyTable.getHostById(fromId);
	struct hostNode * toHost = topologyTable.getHostById(toId);

	struct routeItem * route;
	struct switchNode * switchNode;

	int portDeSortie;
	string nameNextSwitch = fromHost->dstName;

	cout << "------------------------------------------------------" << endl;
	cout << "Src : " << fromHost->name << " Dest : " << toHost->name << endl << endl;
	cout << "Nom du switch suivant : " << nameNextSwitch << endl;

	while (nameNextSwitch.compare(toHost->name) != 0)
	{
		route = routingTable.getTableByName(nameNextSwitch);
		switchNode = topologyTable.getSwitchByName(nameNextSwitch);

		portDeSortie = route->outport.at(distance(route->dstInfo.begin(), find(route->dstInfo.begin(), route->dstInfo.end(), toHost->name)));
		cout << "Port de sortie : " << portDeSortie << endl;

		nameNextSwitch = switchNode->dstName.at(distance(switchNode->srcPort.begin(), find(switchNode->srcPort.begin(), switchNode->srcPort.end(), portDeSortie)));
		cout << "Nom du switch suivant : " << nameNextSwitch << endl;

		count++;
	}

	cout << "From " << fromHost->name << " to " << toHost->name << ": Hop Count = " << count << endl;
	return count;
}

/**
 * Méthode qui implémente la métrique Minhop.
 */
int Calculation::calculate() 
{
	int minHop = -1, nbHop;
	getHopCount(0, 8);

	/*for (int i = 0; i < topologyTable.getHostCount(); i++)
		for (int j = 0; j < topologyTable.getHostCount(); j++)
			if (i != j)
			{
				nbHop = getHopCount(i, j);

				if (nbHop < minHop || minHop == -1) // Besoin de la condition -1 car il faut bien initialiser une première fois la valeur minHop.
					minHop = nbHop;
			}*/

	return minHop;
}

/**
 * Méthode qui calcule la charge d'un noeud
 * source jusqu'au noeud destination.
 */
int Calculation::getRoute(int fromId, int toId)
{
	struct hostNode * fromHost = topologyTable.getHostById(fromId);

	string fromNode = fromHost->name;

	string toNode = topologyTable.getSwitchById(toId)->name;
	
	cout << "From " << fromNode << " to " << toNode;

	string switchName = fromHost->dstName;


	//TODO
	//Parcourir la table de routage du noeud fromId vers le toId
	//Aide : Regarder la structure routeItem et switchNode elles pourront vous aider.
	//Aide : struct routeItem * item = routingTable.getTableByName(switchName); permet de charger la table de routage
	//Retourner 1 si le noeud toId est atteilgnable depuis fromId sinon 0
	
}

/**
 * Méthode qui implémente la métrique nombre de chemins disjoints.
 */
int Calculation::balance() 
{
	int cpt = 0 ; 
	
	//TODO 
	//Implémenter l'algo du calcul de chemins disjoints 
	//Aide : Pour recueperer le nombre de sauts de source vers destination -> getHopCount(source, destination);
	//Aide : Pour recuperer le nombre de HCA -> topologyTable.getHostCount();
	//retourner la valeur maximale trouvée

	return cpt ;
}

