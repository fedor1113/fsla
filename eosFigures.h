#ifndef __EOSFIGURES_H_
#define __EOSFIGURES_H_

/*
	�����, ���������� �� ���������� ���� ������ ��� ��������, 
	��������������� �������� ��������� ���������.
*/

#include "eos.h"
#include "eosTable.h"

class EOSFigures
{
public:
	EOSFigures(EOS* _eos);
	void writeIsoterms(char *outputFileName);
	void writePiEi(char *outputFileName);
	void writePeEe(char *outputFileName);
	void testPiT(double roMin, double roMax, double T, double nIntervals);
	void testEiT(double roMin, double roMax, double T, double nIntervals);
	void testeEOSTe(double ro, double T, double TeMin, double TeMax, double nIntervals);

	void writeIsochor(char *outputFileName, double ro);
	void writeIsoterm(char *outputFileName, double ti);

	void writeEiDiagram(char *outputFileName, double ro_temp, double ei,
		                double dv_temp, double tau, double dm);
	void writekappa(char *outputFileName, double ro);

	void writeAdiabatic(char *outputFileName);

	void writeEntropy(char *outputFileName);

	void writeIsentrope(char *outputFileName);

	void writePiRoTDiagram(char *outputFileName);

	void writeColdCurve(char* outputFileName);


	EOS	 &getEOS() { return *eos; }

private:
	EOS* eos;

	double getTiFromEntropy(double ro, double s, double low_border, double high_border);
};




#endif