#pragma once

#include <fstream>

class FatTree
{
public:
	FatTree(int k);
	void printEntete();
	void printNode();
	void closeFile();

private:
	int k, nbServeurAll, nbServeur, nbEdgeAll, nbEdge, nbCore;
	std::ofstream fichier;
};