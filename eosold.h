#ifndef _EOS_H_
#define _EOS_H_

#include <complex>

using namespace std;

//typedef <complex>double cd

// �������� ��� ���������� ������� �����������

#define EOS_EPS 1.0e-5
#define EOS_EPS_RO 10.0
#define EOS_EPS_TI 1.0

/*
��� ������ ��� ����������� ���� ��������� ��������� -- ����������, 
��������������, ���� ��������� ��������� ��� ���������� ����
(���������-���������)
*/

enum EOSType {none, table, analytic, ideal, test, 
	          analyticNi, tableNi, 
			  analyticTa, tableTa, 
			  analyticFe, tableFe, tableFeAlpha, 
			  analyticAu, tableAu, simpleAu,
			  analyticPyrexGlass, 
			  simpleCr, simpleSi,
			  simpleWater,
			  MieGruneisen, bin};

/* 
����� EOS -- ����������� ������� ����� ��� ��������� �������, 
����������� ��������� ���������. ������ ���� ������� -- 
��������� �������� ���������� ��������� ��������� �� �����
���������� � ���������.

��� ����� EOS �������� ����� ����������� �������, ������� 
������ ������������� ��������� ��������� � ���������: ������ 
�������� �� ����������� � ���������, ����������� �� ��������� � 
������� � �.�.

��������� ��������� ����� ����:
- ������������� ��� ������������� ��������;
- ������������� ��� ���������� ����;
- ���������.

��� ���������� ��������� � �������� � ������� ������ ��.

����� ����� ������ ��������� � �������� ����� �������� 
������������� ��������� ����������� ���������� �������.

�������� �������� �����-���� ������ ��������� ��������� �� 
������ ����� ������. ���������� ������ ������������ ������.
*/

class EOSOld { 
public:
	virtual EOSType getType()=0;
	virtual double    getpi(double ro, double ti)=0;
	virtual double    getpe(double ro, double ti, double te)=0;
			double	   getp(double ro, double ti, double te) {return getpi(ro, ti) + getpe(ro, ti, te); }	
	virtual double    getei(double ro, double ti)=0;
	virtual double    getee(double ro, double ti, double te)=0;
	virtual double	   gete(double ro, double ti, double te) {return getei(ro, ti) + getee(ro, ti, te); }			
	virtual double    getti(double ro, double ei)=0;
	virtual double    gette(double ro, double ti, double ee)=0; 
	virtual double    getci(double ro, double ti)=0;
	virtual double    getce(double ro, double te)=0;
	virtual double     getC(double ro, double ti, double te)=0;
	virtual double getAlpha(double ro, double ti, double te)=0;
	virtual double getkappa(double ro, double ti, double te)=0;
	virtual double getEntropy(double ro, double T)=0; 
	virtual double getGamma(void)=0;
	// Phase features
	virtual double getphase(double ro, double ti)=0;
	virtual double   getmix(double ro, double ti)=0; 
	// ee(...) inverting
	double   getdeedte_ro(double ro, double ti, double te);
	// Service and auxilary procedures
	double   getMAX_T(void) { return MAX_T; }
	double	 getMIN_T(void) { return MIN_T; }
	double	getMAX_RO(void) { return MAX_RO; }
	double  getMIN_RO(void) { return MIN_RO; }
	double  getro0(void)    { return ro0; }    
protected:
	double ro0;
	double MAX_T, MIN_T;
	double MAX_RO, MIN_RO;
};

#endif
