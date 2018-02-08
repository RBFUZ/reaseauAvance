#include "FatTree.h"
#include <iostream>
#include <string>
#include <fstream>
#include <stdlib.h>
#include <math.h>

using namespace std;


FatTree::FatTree(void)
{

}

int main(int argc, char *argv[])
{
	cout << argc << endl;

	//	Vérifie que 1 argument a été saisi et que la valeur de l'argument est un nb pair >=2
	if (argc != 2) {
		cout << "One argument is expected" << endl;
	}

	int k = atoi(argv[1]);
	if (k % 2 != 0 || k < 2) {
		cout << "The value of the argument is invalid" << endl;
	}

	
	// Création et ouverture en écritre du fichier topogen.cpp
	ofstream fichier("topogen.cpp", ios::out | ios::trunc);

	// 
	fichier << "#fat topology file." << endl;
	fichier << "#Value of k = " << k << endl;
	fichier << "#Total number of hosts = " << k * pow((k / 2), 2) << endl;
	fichier << "Number of hosts under each switch = " << k / 2 << endl;
	fichier << "#############################################################################" << endl;

	fichier.close();

	return 0;
}