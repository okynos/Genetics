/*
 * Population.h
 *
 *  Created on: 20 dic. 2016
 *      Author: okynos
 */

#ifndef POPULATION_H_
#define POPULATION_H_

#include <vector>
#include "Data.h"
using namespace std;

class Population {
private:
	vector<vector<unsigned> > members;
	vector<pair<unsigned long int, unsigned> > fitness;
	vector<vector<unsigned> > recombined;
	Data data;
	unsigned numGens;
	void initialize();
public:
	Population();
	~Population();
	Population(const unsigned & numMembers, const unsigned & numGenSet, const char * filename);
	const void select();
	const unsigned long int calculateGenFitness(const vector<unsigned> & individual, const unsigned & i, const unsigned & j);
	const void evaluate();
	const void evaluateBaldwin();
	const void evaluateLamarck();
	const void evaluateLamarck2();
	const vector<unsigned> recombinePair(const vector<unsigned> & father, const vector<unsigned> & mother);
	const void recombine();
	const void mutate();
	const long int best();
	const vector<unsigned> getBestIndividual();
	const unsigned long int contrast(const vector<unsigned> & permutation);
	const vector<unsigned> opt(const vector<unsigned> & member, const unsigned long int & fitness, unsigned long int & best);
};

#endif /* POPULATION_H_ */
