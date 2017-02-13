/*
 * Data.h
 *
 *  Created on: 20 dic. 2016
 *      Author: okynos
 */

#ifndef DATA_H_
#define DATA_H_

#include<iostream>
#include<fstream>
#include<vector>
using namespace std;

class Data {
private:
	vector<vector<int> > distance;
	vector<vector<int> > weight;
public:
	Data();
	void readFile(const char * filename);
	unsigned size();
	int getDistance(unsigned i, unsigned j);
	int getWeight(unsigned i, unsigned j);
};

#endif /* DATA_H_ */
