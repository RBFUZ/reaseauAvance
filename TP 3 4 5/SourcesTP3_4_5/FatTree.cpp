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
	fichier << "#Number of hosts under each switch = " << k / 2 << endl;
	fichier << "#############################################################################" << endl;
}

void FatTree::printNode()
{
	int port = 2;
	int numNode = 0;

	// Changer de pods
	for (int pod = 0; pod < k; pod++)
	{
		// Changer de switch
		for (int swh = 0; swh < nbEdge; swh++)
		{
			// Créer le nombre de serveur pour un switch
			for (int hote = 0; hote < nbEdge; hote++)
			{
				fichier << "Hca		1		\"Node(" << numNode++ << ")\"" << endl;
				fichier << "[1]  \"Edge(" << pod << " " << swh << " 1)\"[" << port << "]" << endl;
				port += 2;
			}
			port = 2;
		}
	}
	fichier << endl;
}

void FatTree::printSwitchEdge()
{
	int numHost = 0;
	for (int iBoucle1 = 0; iBoucle1 < k; iBoucle1++)
	{
		for (int iBoucle2 = 0; iBoucle2 < nbEdge; iBoucle2++)
		{
			fichier << "Switch		" << k << "		\"Edge(" << iBoucle1 << " " << iBoucle2 << " 1)\"" << endl;

			//Liaison avec chaque aggrégation et serveur
			for (int iBoucle3 = 0; iBoucle3 < 2 * nbEdge; iBoucle3++)
			{
				if (iBoucle3 % 2 == 0)
					fichier << "[" << iBoucle3 + 1 << "]  \"Aggr(" << iBoucle1 << " " << (k / 2) + iBoucle3 / 2 << " " << 1 << ")\"[" << (iBoucle2 + 1) * 2 << "]" << endl;
				else 
					fichier << "[" << iBoucle3 + 1 << "]  \"Node(" << numHost++ << ")\"[1]" << endl;
			}
		}
	}
}

// Génération des liaisons sur les switchs aggrégations
void FatTree::printSwitchAggr()
{
	int indice = 0, port = 2;

	// Une iteration = un pod
	for (int pod = 0; pod < k; pod++)
	{
		// Une iteration = un switch
		for (int sw = k/2; sw < nbEdge * 2; sw++)
		{
			fichier << endl << "Switch		" << k << "		\"Aggr(" << pod << " " << sw << " 1)\"" << endl;

			// Création des noeuds avec les cores et les edges
			for (int l = 1; l < nbEdge * 2; l++)
			{
				fichier << "[" << l << "] \"Core(" << k << " " << port / 2 << " " << indice + 1 << ")\"[" << pod + 1 << "]" << endl;
				l++;
				fichier << "[" << l << "] \"Edge(" << pod << " " << indice << " 1)\"[" << port - 1 << "]" << endl;

				indice++;
			}
			indice = 0;
			port += 2;
		}
		port = 2;
	}
}

// Génération des liaisons avec les switchs aggregations
void FatTree::printSwitchCore()
{
	int port = 1;
	int midCore = k / 2;

	// Une iteration = deux cores
	for (int pod = 1 ; pod <= nbEdge; pod++)
	{
		// Une iteration = un core
		for (int j = 1; j <= nbEdge; j++)
		{
			fichier << endl << "Switch		" << k << "		\"Core(" << k << " " << pod << " " << j << ")\"" << endl;

			// k iteration
			for (int i = 0; i < k; i++)
			{
				fichier << "[" << i + 1 << "] \"Aggr(" << i << " " << midCore << " 1)\"[" << port << "]" << endl;
			}
			port += 2;
		}
		port = 1;
		midCore++;
	}
}

// Fermeture du fichier
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
		if (k % 2 != 0 || k < 4)
			cout << "The value of the argument is invalid" << endl;
		else 
		{
			FatTree fat(k);
			fat.printEntete();
			fat.printNode();
			fat.printSwitchEdge();
			fat.printSwitchAggr();
			fat.printSwitchCore();
			fat.closeFile();
		}
	}
	return 0;
}
