#ifndef EOSTABLE_SCALE_H
#define EOSTABLE_SCALE_H

#include <cassert>
#include <string>

class EOSTScale {
public:
	EOSTScale();
	~EOSTScale();
	void	create(int _nSize, double _minV, double _maxV, double scaler);
	void	clear();
	int		getLeftIdx(double t);
	int		getSize() { return nSize; }
	double	getMin()  { return minV; }
	double	getMax()  { return maxV; }
	void	getFromFile(const char* fName, std::string dirName, int _nSize, double _minV, double _maxV, double scaler); 
	inline double operator [] (const int i) const {
        assert( i >=0 && i < nSize );
        return scale[i];
    }
private:
	double *scale;
	int nSize;
	double maxV, minV; 
	void xchg(double *a, double *b);
};

#endif
