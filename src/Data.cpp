/*
 * Data.cpp
 *
 *  Created on: 20 dic. 2016
 *      Author: okynos
 */

#include "Data.h"

Data::Data() {}

void Data::readFile(const char * filename){
	ifstream file;
	file.open(filename);
	int matrixSize;

	if (file.is_open()) {
		file >> matrixSize;
		distance = vector<vector<int> >(matrixSize, vector<int>(matrixSize));
		weight = vector<vector<int> >(matrixSize, vector<int>(matrixSize));

		for(unsigned i=0; i<distance.size(); ++i){
			for(unsigned j=0; j<distance.size(); ++j){
				file >> distance[i][j];
			}
		}
		for(unsigned i=0; i<weight.size(); ++i){
			for(unsigned j=0; j<weight.size(); ++j){
				file >> weight[i][j];
			}
		}
	}
	file.close();
}

unsigned Data::size(){
	return distance.size();
}

int Data::getDistance(unsigned i, unsigned j){
	return distance[i][j];
}

int Data::getWeight(unsigned i, unsigned j){
	return weight[i][j];
}

