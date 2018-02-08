#include "FatTree.h"
#include <iostream>
#include <string>
#include <fstream>

using namespace std;


FatTree::FatTree(void)
{

}

int main(int argc, char *argv[])
{
	// Création et ouverture en écritre du fichier topogen.cpp
	ofstream fichier("topogen.cpp", ios::out | ios::trunc);

	// 
	fichier << "#fat topology file.";

	fichier.close();

	return 0;
}