#pragma once

#include <fstream>

class FatTree
{
public:
	FatTree(int k);
	void printEntete();
	void printNode();
	void printSwitchEdge();
	void printSwitchAggr();
	void printSwitchCore();
	void closeFile();

private:
	int k, nbServeurAll, nbServeur, nbEdgeAll, nbEdge, nbCore;
	std::ofstream fichier;
};