/*
 * Population.cpp
 *
 *  Created on: 20 dic. 2016
 *      Author: okynos
 */

#include "Population.h"
#include <cstdlib>
#include <vector>
#include <algorithm>
using namespace std;

Population::Population() {numGens = 0;}

Population::~Population(){}

Population::Population(const unsigned & numMembers, const unsigned & numGenSet, const char * filename){
	numGens = numGenSet;
	members = vector<vector<unsigned> >(numMembers, vector<unsigned>(numGens));
	fitness = vector<pair<unsigned long int, unsigned> >(numMembers);
	recombined = vector<vector<unsigned> >(fitness.size(), vector<unsigned>(numGens));

	for(unsigned i=0, k=1; i<numMembers; ++i){
		k = 1;
		for(unsigned j=0; j<numGens; ++j){
			members[i][j] = k;
			k++;
		}
	}
	data.readFile(filename);
	initialize();
}

void Population::initialize(){
	int exchanger = 0, random = 0, max = numGens-1, min = 0;
	for(unsigned i=0; i<members.size(); ++i){
		for(unsigned j=0; j<numGens; ++j){
			min = j;
			random = rand() % (max-min + 1) + min;
			exchanger = members[i][j];
			members[i][j] = members[i][random];
			members[i][random] = exchanger;
		}
	}
}

const bool compare(const pair<unsigned long int, unsigned> &left, const pair<unsigned long int, unsigned> &right){
	    return left.first < right.first;
}

const void Population::select(){
	sort( fitness.begin(), fitness.end(), compare);
}

const unsigned long int Population::calculateGenFitness(const vector<unsigned> & individual, const unsigned & i, const unsigned & j){
	unsigned long int difFit = 0;
	for(unsigned t=0; t<numGens; ++t){
		difFit += data.getWeight(i, t) * data.getDistance(individual[i]-1, individual[t]-1);
		difFit += data.getWeight(j, t) * data.getDistance(individual[j]-1, individual[t]-1);
		if(i!=t && j!=t){
			difFit += data.getWeight(t, i) * data.getDistance(individual[t]-1, individual[i]-1);
			difFit += data.getWeight(t, j) * data.getDistance(individual[t]-1, individual[j]-1);
		}
	}
	return difFit;
}


const void Population::evaluate(){
	unsigned long int sum;
	for(unsigned k=0; k<members.size(); ++k){
		sum = contrast(members[k]);
		fitness[k].first = sum;
		fitness[k].second = k;
		sum = 0;
	}
}

const void Population::evaluateBaldwin(){
	unsigned long int sum, best;

	for(unsigned k=0; k<members.size(); ++k){
		sum = contrast(members[k]);
		best = sum;
		opt(members[k], sum, best);
		fitness[k].first = best;
		fitness[k].second = k;
		sum = 0;
	}
}

const void Population::evaluateLamarck(){
	unsigned long int sum, best, bestFound;

	for(unsigned k=0; k<members.size(); ++k){
		sum = contrast(members[k]);
		best = sum;
		members[k] = opt(members[k], sum, best);
		fitness[k].first = best;
		fitness[k].second = k;
		if(best < bestFound){
			bestFound = best;
		}
		sum = 0;
	}
}

const void Population::evaluateLamarck2(){
	unsigned long int sum, best, median = 0;

	for(unsigned k=0; k<members.size(); ++k){
		sum = contrast(members[k]);
		best = sum;
		median += best;
		if(best < median/(k+1)){
			members[k] = opt(members[k], sum, best);
		}
		fitness[k].first = best;
		fitness[k].second = k;
		sum = 0;
	}
}

const vector<unsigned> Population::recombinePair(const vector<unsigned> & father, const vector<unsigned> & mother){
	vector<unsigned> child = vector<unsigned>(numGens);
	unsigned j, k, numGensCopied = 0, randomGenInit, genSize = numGens/2;

	randomGenInit = rand() % (numGens/2);

	for(unsigned i=randomGenInit; i<randomGenInit+genSize; ++i){
		child[i] = father[i];
		numGensCopied++;
	}
	k = j = randomGenInit + genSize;

	while(numGensCopied != numGens){
		if( find(child.begin(), child.end(), mother[k]) == child.end() ){
			child[j] = mother[k];
			numGensCopied++;
			j = (j+1) % numGens;
		}
		k = (k+1) % numGens;
	}
	return child;
}

const void Population::recombine(){
	unsigned long int bestA = 999999999, bestB = 999999999;
	unsigned limit = 5, randomA, randomB;
	vector<unsigned> selectedA, selectedB, individualA, individualB;

	for(unsigned i=0, k=0; i<members.size()-2; ++i){
		for(unsigned j=0; j<limit; ++j){
			 randomA = rand() % members.size();
			 randomB = rand() % members.size();
			 selectedA.push_back(randomA);
			 selectedB.push_back(randomB);
		}
		for(unsigned j=0; j<selectedA.size(); ++j){
			if(fitness[selectedA[j]].first <= bestA){
				bestA = fitness[selectedA[j]].first;
				individualA = members[selectedA[j]];
			}
			if(fitness[selectedB[j]].first <= bestB){
				bestB = fitness[selectedB[j]].first;
				individualB = members[selectedB[j]];
			}
		}
		recombined[k] = recombinePair(individualA, individualB);
		k++;
		selectedA.clear();
		selectedB.clear();
	}

	unsigned t = fitness.size()-1;
	for(unsigned i=0; i>members.size()-5; ++i){
		members[fitness[t].second] = recombined[i];
	}
}

const void Population::mutate(){
	unsigned randomGenB, randomSelector, switcher;
		for(unsigned i=0; i<members.size(); ++i){
			for(unsigned j=0; j<numGens; ++j){
				randomSelector = rand() % numGens;
				if(randomSelector == members[i][j]){
					randomGenB = rand() % numGens;
					switcher = members[i][j];
					members[i][j] = members[i][randomGenB];
					members[i][randomGenB] = switcher;
				}
				randomSelector = rand() % numGens;
				if(randomSelector == members[i][j]){
					randomGenB = rand() % numGens;
					switcher = members[i][j];
					members[i][j] = members[i][randomGenB];
					members[i][randomGenB] = switcher;
				}
			}
	}

}

const long int Population::best(){
	unsigned long int best = 999999999;
	for(unsigned i=0; i<fitness.size(); ++i){
		if(fitness[i].first < best)
			best = fitness[i].first;
	}
	return best;
}

const vector<unsigned> Population::getBestIndividual(){
	return members[fitness[0].second];
}

const unsigned long int Population::contrast(const vector<unsigned> & permutation){
	unsigned long int sum = 0;
	for(unsigned i=0; i<data.size(); ++i){
		for(unsigned j=0; j<data.size(); ++j){
			sum += data.getWeight(i, j) * data.getDistance(permutation[i]-1, permutation[j]-1);
		}
	}
	return sum;
}

const vector<unsigned> Population::opt(const vector<unsigned> & member, const unsigned long int & fitness, unsigned long int & best){
	unsigned long int optFitFirst, optFitSecond, calcFit, better = fitness;
		vector<unsigned> individual, middleIndividual = member , bestIndividual = member;
		unsigned switcher;

		for(unsigned i=0; i<numGens; ++i){
			for(unsigned j=i+1; j<numGens; ++j){
				individual = middleIndividual;
				optFitFirst = calculateGenFitness(individual, i, j);

				switcher = individual[i];
				individual[i] = individual[j];
				individual[j] = switcher;

				optFitSecond = calculateGenFitness(individual, i, j);
				calcFit = better - optFitFirst + optFitSecond;
				if(calcFit < best){
					best = calcFit;
					bestIndividual = individual;
				}
			}
			better = best;
			middleIndividual = bestIndividual;
		}
	return bestIndividual;
}
