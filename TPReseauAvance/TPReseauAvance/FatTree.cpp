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
	// Cr�ation et ouverture en �critre du fichier topogen.cpp
	ofstream fichier("topogen.cpp", ios::out | ios::trunc);

	// 
	fichier << "#fat topology file.";

	fichier.close();

	return 0;
}