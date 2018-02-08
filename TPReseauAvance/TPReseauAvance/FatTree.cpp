#include "FatTree.h"
#include <iostream>
#include <string>
#include <fstream>
#include <stdlib.h>
#include <math.h>

using namespace std;

FatTree::FatTree(int nbPod)
{
	k = nbPod;
	nbServeurAll = int(k * pow((k / 2), 2));
	nbServeur = int(pow((k / 2), 2));
	nbEdgeAll = (k * k) / 2;
	nbEdge = k / 2;
	nbCore = int(pow((k / 2), 2));

	// Création et ouverture en écritre du fichier topogen.cpp
	fichier = ofstream("topogen.cpp", ofstream::out);
}

void FatTree::printEntete()
{
	fichier << "#fat topology file." << endl;
	fichier << "#Value of k = " << k << endl;
	fichier << "#Total number of hosts = " << nbServeurAll << endl;
	fichier << "Number of hosts under each switch = " << k / 2 << endl;
	fichier << "#############################################################################" << endl;
}

void FatTree::printNode()
{
	int port = 2;
	// Itération sur l'ensemble des serveurs
	for (int numNode = 0; numNode < nbServeurAll; numNode++)
	{
		// Changer de pods
		for (int pod = 0; pod < k; pod++)
		{
			// Changer de switch
			for (int swh = 0; swh < nbEdge; swh++)
			{
				// Créer le nombre de serveur pour un switch
				for (int hote = 0; hote < nbEdge; hote++)
				{
					fichier << "Hca		1		\"Node(" << numNode << ")\"" << endl;
					fichier << "[1]  \"Edge(" << pod << " " << swh << " 1)\"[" << port << "]" << endl;
					numNode++;
					port += 2;
				}
				port = 2;
			}
		}
	}
	fichier << endl;
}

void FatTree::printSwitchEdge()
{
	for (int i = 0; i < k; i++)
	{
		for (int j = 0; j < nbEdge; j++)
		{
			fichier << "Switch		" << k << "		\"Edge(" << i << " " << j << " 1)\"" << endl;
		}
	}
}

void FatTree::closeFile()
{
	fichier.close();
}


int main(int argc, char *argv[])
{
	//	Vérifie que 1 argument a été saisi et que la valeur de l'argument est un nb pair >=2
	if (argc != 2) 
		cout << "One argument is expected" << endl;
	else 
	{
		// Verifie que le k est pair et superieur Ã  1
		int k = atoi(argv[1]);
		if (k % 2 != 0 || k < 2)
			cout << "The value of the argument is invalid" << endl;
		else 
		{
			FatTree fat(k);
			fat.printEntete();
			fat.printNode();
			fat.printSwitchEdge();
		}
	}

	return 0;
}