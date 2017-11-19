#include "HArea.h"
#include "HCriterion.h"
#include "HFunction.h"
#include "HOptimization.h"
using namespace std;

mt19937 mt_rand(time(0));
uniform_real_distribution<>u(0, 1);


deque<vector<double> > Optimization::getTrajectory() {
	return 	trajectory;
}
const char* FletcherRivs::getMethodName() const {
	return "Fletcher Rivs method";
}


/**
\brief It finds the distance to the nearest boundary of the area in a given direction
\param[in] x starting point
\param[in] D area of minimization
*/
const double FletcherRivs::findBorderAlpha(const vector<double>& x,
	const  Area& D) const {
	double border = FOR_BORDER;
	double temp = FOR_BORDER;
	for (int i = 0; i < x.size(); ++i) {
		if (p[i] > 0) temp = (D.getRight()[i] - x[i]) / p[i];
		if (p[i] < 0) temp = (D.getLeft()[i] - x[i]) / p[i];
		if (fabs(temp) < border) border = fabs(temp);
	}
	return border;
}



vector<double> FletcherRivs::minimize(vector<double> x, const Function& f,
	const  Criterion& c) {
	double b = 0; double a = 1;
	double epsilon_for_argmin = c.getEps();
	trajectory.push_back(x);//��������� ����� ���� �������� � ����������
	vector<double> r0(f.getGradient(x));
	vector<double> x0(x);
	int noChange(0);
	p = (-1)*r0;
	vector<double> r(x.size());
	for (int k = 0; (!c.stop(x, x0, f, k, noChange) && a) || !k; ++k) {
		x0 = x;
		a = calculateArgmin(x, f, epsilon_for_argmin);
		x = x + a*p;
		r = f.getGradient(x);
		b = scalar_prod(r, r) / scalar_prod(r0, r0);
		p = (-1)*r + b*p;
		r0 = r;
		trajectory.push_back(x);//��������� �������� 
		newIteration();
		if (x == x0) ++noChange;
	}
	return x;
}

/**
\brief It finds the minimum point of the objective function in a given direction
\param[in] x starting point
\param[in] f objective function
\param[in] argmineps accuracy
\return a positive number equal to the distance from the starting point to the point of minimum of the objective function in the given direction
*/
double FletcherRivs::calculateArgmin(const vector<double>& x, const Function& f,
	double argmineps) const {
	double l = 0, r = findBorderAlpha(x, f.getArea());
	double m = (l + r) / 2;
	CriterionOneDimNorm c(argmineps*0.1);
	for (int k = 0; !c.stop(vector<double>(1,
		                    f.getDirectionalDerivative(x + m*p, p)),
		                    x, f, k); ++k) {
		if (f.getDirectionalDerivative(x + m*p, p) > 0)
			r = m;
		else l = m;
		m = (l + r) / 2;
	}
	return m;
}

/**
\brief It simulates uniform distribution in a given area
\param[in] D area for simulates
\return a vector having a uniform distribution in the area D
*/
vector<double> RandomSearch::simulateUniformInD(const Area& D) {
	int dim = D.getLeft().size();
	vector<double> randx;
	for (int k = 0; k < dim; ++k) {
		randx.push_back(D.getLeft()[k] + (D.getRight()[k] - D.getLeft()[k])*
			u(mt_rand));
	}
	return randx;
}

RandomSearch::RandomSearch(const Area& D, double probability, int whenSTOP,
	double whatchange) :p(probability),
	stopIfnoChange(whenSTOP), change(whatchange) {
	radius = initializeRadius(D);
	radiusChange = radius;
}
double RandomSearch::initializeRadius(const Area& D) const {
	double mind = 0;
	for (int i = 0; i < D.getDim(); ++i) {
		double temp = D.getRight()[i] - D.getLeft()[i];
		mind = mind > temp ? temp : mind;
	}
	return mind;
}
const char* RandomSearch::getMethodName() const { return "Random Search"; }
vector<double> RandomSearch::minimize(vector<double> x, const Function& f,
	const   Criterion& c) {
	int dim = f.getDim();
	vector<double>y(dim);
	vector<double>y0(dim);
	vector<double> leftB(dim);
	vector<double> rightB(dim);
	bool flag;

	//x = simulateUniformInD(f.getArea());
	y = x;
	for (int i = 0, no_change = 0; !c.stop(y, y0, f, i, no_change); ++i) {
		if (u(mt_rand) < p) {
			x = simulateUniformInD(f.getArea());
			flag = true;
		}
		else {
			for (int k = 0; k < dim; ++k) {
				leftB[k] = y[k] - radiusChange > f.getArea().getLeft()[k] ?
				           y[k] - radiusChange : f.getArea().getLeft()[k];
				rightB[k] = y[k] + radiusChange < f.getArea().getRight()[k] ?
					        y[k] + radiusChange : f.getArea().getRight()[k];
			}
			Area B(leftB, rightB);
			x = simulateUniformInD(B);
			radiusChange *= change;
			flag = false;
		}
		if (f.f(y) > f.f(x)) {
			y0 = y;
			y = x;
			no_change = 0;
			if (flag) radiusChange = radius;
		}
		else ++no_change;
		newIteration();
		trajectory.push_back(y);
	}
	return y;
}



