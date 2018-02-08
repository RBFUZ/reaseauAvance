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
	int edge1 = 0, edge2 = 0, edge3 = 1, port = 0, changeSwitch = 0, changePod = 1;
	for (int i = 0; i < nbServeurAll; i++)
	{
		fichier << "Hca		1		\"Node(" << i << ")\"" << endl;

		port = port + 2;

		// Changement de switch
		if (changeSwitch == nbEdge)
		{
			// Changement de pod
			if (changePod == nbEdge)
			{
				edge1++;
				edge2 = -1;
				changePod = 0;
			}
			edge2++;
			changeSwitch = 0;
			port = 2;
			changePod++;
		}

		fichier << "[1]  \"Edge(" << edge1 << " " << edge2 << " " << edge3 << ")\"[" << port << "]" << endl;
		changeSwitch++;
	}
	cout << endl << endl;
}

void FatTree::closeFile()
{
	fichier.close();
}


int main(int argc, char *argv[])
{
	//	Vérifie que 1 argument a été saisi et que la valeur de l'argument est un nb pair >=2
	if (argc != 2) {
		cout << "One argument is expected" << endl;
	}
	else {
		// Verifie que le k est pair et superieur Ã  1
		int k = atoi(argv[1]);
		if (k % 2 != 0 || k < 2) {
			cout << "The value of the argument is invalid" << endl;
		}
		else {
			FatTree fat(k);
			fat.printEntete();
			fat.printNode();
		}
	}

	return 0;
}
