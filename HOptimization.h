#pragma once
#include "stdafx.h"
#include <cstdio>
#include <iostream>
#include <cmath>
#include <math.h>
#include <vector>
#include <iomanip>
#include<random>
#include "HArea.h"
#include "HCriterion.h"
#include"Hother.h"
#include "HFunction.h"
#include <deque>
using namespace std;
/**
\file
\brief Header file describing the class Optimization and its heirs
*/

/**
\brief Abstract class for solve the problem of multidimensional optimization
*/
class Optimization {
protected:
	int counter = 0;
    deque<vector<double> >trajectory;
public:
	/**
	\brief It finds a minimum point with given parameters
	\param[in] x starting point
	\param[in] f objective function
	\param[in] c1 break criterion
	\return approximation of the vector x on which the objective function reaches a minimum
	*/
	virtual vector<double> minimize(vector<double> x, const Function& f,
		const  Criterion& c) = 0;
	virtual const char* getMethodName() const = 0;
	int getCounter() const { return counter; }
	void newIteration() { ++counter; }
	deque<vector<double> > getTrajectory();
    void clearTrajectory();
    void clearCounter();
};

/**
\brief The class implements the Fletcher-Reeves method
*/
class  FletcherReeves :public Optimization {
    const int FOR_BORDER =1000000;
	vector<double> p;
public:
	virtual const char* getMethodName() const;
	const double findBorderAlpha(const vector<double>& x, const Area& D) const;
	virtual vector<double> minimize(vector<double> x, const Function& f,
		const Criterion& c) override;
	double calculateArgmin(const vector<double>& x, const Function& f,
		double) const;
};

/**
\brief The class implements the random search method
*/
class RandomSearch : public Optimization {
	double p;
	double change;
	vector<double> simulateUniformInD(const Area& D);
public:
    RandomSearch( double probability = 0.8,
		double whatChange = 0.9);
	double initializeRadius(const Area& D) const;
	virtual const char* getMethodName() const;
	virtual vector<double> minimize(vector<double> x, const Function& f,
		const Criterion& c) override;
};


