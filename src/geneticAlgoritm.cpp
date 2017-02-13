//============================================================================
// Name        : geneticAlgoritm.cpp
// Author      : Jos� Luis Fern�ndez
// Version     :
// Copyright   : Jos� Luis Fern�ndez Copyright
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "Data.h"
#include "Population.h"
#include <ctime>
#include <cstdlib>
using namespace std;

int main() {
	srand(time(NULL));
	Population population(100, 256, "data/tai256c.dat");
	int generation = 0;
	unsigned long int best = 999999999, better = 999999999;
	static const unsigned arr[] = {193,71,93,23,139,95,249,183,8,136,167,216,19,198,200,41,180,175,89,210,252,9,229,91,195,27,239,17,168,208,65,245,145,18,143,138,48,127,90,228,170,240,3,172,100,50,191,56,63,235,153,12,233,132,224,5,92,57,222,178,33,171,129,159,109,141,54,144,15,162,2,207,78,164,122,77,116,68,120,75,220,76,157,103,174,64,231,118,101,24,192,181,85,98,52,107,21,97,43,106,40,199,254,20,160,146,49,130,140,256,244,108,121,36,196,53,217,113,88,173,46,117,206,26,125,152,13,232,215,163,28,176,247,42,238,147,248,70,179,230,87,128,205,38,255,7,165,227,29,190,51,104,81,234,83,253,124,59,166,218,25,202,194,66,201,236,223,82,161,150,226,72,135,241,73,133,251,47,142,243,35,250,55,188,22,246,79,105,99,58,137,74,44,154,242,61,169,16,119,204,187,67,186,182,37,225,115,96,219,111,84,94,221,197,32,156,45,151,131,69,123,80,237,1,158,11,110,6,149,14,209,30,134,184,34,213,211,177,4,212,39,214,126,189,62,102,10,155,185,31,114,86,203,60,112,148}; //44884696 Best Found: 44872090

	vector<unsigned> permutationToContrast(arr, arr + sizeof(arr) / sizeof(arr[0]));
	vector<unsigned> bestIndividual;
	bool contrast = true;

	while(generation < 50 && !contrast){
		population.evaluateLamarck();
		population.select();

		better = population.best();

		if(better < best){
			best = better;
			bestIndividual =  population.getBestIndividual();
		}

		cout << generation << " " << better << " " << best << " (";
		for(unsigned i=0; i<bestIndividual.size(); ++i)
			cout << bestIndividual[i] << ", ";
		cout << ")" << endl;

		generation += 1;
		population.recombine();
		population.mutate();
	}

	if(contrast){
		cout << population.contrast(permutationToContrast) << endl;
	}

	cout << "Fin" << endl;
	return 0;
}
