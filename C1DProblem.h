#ifndef _C1DPROBLEM_H_
#define _C1DPROBLEM_H_

#include<string>

using namespace std;


class C1DProblem {	
public:
	C1DProblem(string _name, 
		       double _rol, double _ul, double _pl, double _ror, double _ur, double _pr, 
			   double _xmin, double _xmax, double _tmin, double _tmax, double _x0,
			   int _nx, double _cfl, string _bcs) : name(_name), rol(_rol), ul(_ul), pl(_pl), ror(_ror), ur(_ur), pr(_pr),
			   xmin(_xmin), xmax(_xmax), tmin(_tmin), tmax(_tmax), x0(_x0), nx(_nx), cfl(_cfl), bcs(_bcs) {}
	string name;
	const double rol, ul, pl, ror, ur, pr;
	const double xmin, xmax, tmin, tmax, x0;
	const int nx;
	double cfl;	
	string bcs;
};


extern C1DProblem prNBtest;

#endif