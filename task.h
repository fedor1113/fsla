#ifndef _CTask_H_
#define _CTask_H_

#include <stdio.h>
#include <stdlib.h>

#include "defines.h"
#include "method.h"
#include "eos.h"
#include "CTestToro.h"
#include "eos\\EOSBin.h"
//#include "eosTableFeAlpha.h"

/* ���������, ������������ ����. �������������� ������� -- ����� ���. */

struct Zone 
{
	int n;				// ���������� ����� � ����
	double l;			// ������ ����
	double ro;			// ���������
	double te;			// ����������� �����������
	double ti;			// ������ �����������
	double v;			// ��������
	double expProperty;	// ���������� ����������. ���� �� �������, ����������������� 
						// ���������� ���������� ���, ���� ���������.
	double e;
};

/*
   ����� CTask ��������� ���������� ������ �� �������� �����,
   ��������� ������� ������� � �������� ������, ��������
   ��������� ���������, ����� ���������� �������������.


   ������������ �������� �����:
   
   1. ���� �������� � ��������� ������. ������ ������ � ����� -- ������������
      �������� �����-���� ����������. ����� ��������� ���������� ���������.
	  "nZones=5", "nZones =5", "nZones= 5" -- ������� ������������ �������.
	  "nZones = 5" -- ���������� ������.

   2. ������� ���������� ���������� �����.

   3. ������ ���������� � ���������:
	  EOSType = ideal | analytic | table - ��������� ���������
	  Method = euler | lagrange			 - ����� ���������� �������������
	  HydroStage = 0 | 1				 - ����������� �������������?
	  HeatStage = 0 | 1					 - ����������� ����������� ����������������?
	  ExchangeStage = 0 | 1				 - ����������� ����������-������ �����?

	  nZones = 2						 - ���������� ���, ������������ � �����

   4. ������ ���������� ��� ������ ����:
	  l = 100.0e-9  - ����� ����
	  nSize = 50    - ���������� ����� � ����
	  ro = 0.1e-8   - ��������� � ����
	  ti = 300.0    - ������ ����������� � ����
	  te = 0.0      - ����������� ����������� � ����
	  v = 0.0       - �������� � ����
	  exp = 0.0     - ����������������� ��������� � ���� ��� 0

   5. ������ ������ ��� ������ �������� ������ �������.


   ����������� �� ���������� ����������:

   1. Method = euler ������������ ������ EOSType = ideal.

   2. HeatStage = 1, ExchangeStage = 1 � te != 0 ��� 
      EOSType = ideal �� ����� ������.
*/

enum TaskType { undef, RuGlass, LH1D };

class CTask {
public:
	CTask();
	CTask(TaskType _type, bool _bHydroStage, bool _bHeatStage, bool _bExchangeStage, EOS* _eos, EOS* _eosGlass, int _sourceFlag,
		  double _tauPulse, double _fluence, double _deltaSkin, Zone* _zones, unsigned int _nZones, double _maxTime, CMethod* _mtd,
		  int _viscFlag, double _courant, unsigned int _totalSize, int _EOSFlag, int _methodFlag) :
		  type(_type), 
		  bHydroStage(_bHydroStage), bHeatStage(_bHeatStage), bExchangeStage(_bExchangeStage), 
		  eos(_eos), eosGlass(_eosGlass),
		  sourceFlag(_sourceFlag),
		  tauPulse(_tauPulse), fluence(_fluence), deltaSkin(_deltaSkin), 
		  zones(_zones), nZones(_nZones), 
		  maxTime(_maxTime),
		  mtd(_mtd), viscFlag(_viscFlag), courant(_courant), totalSize(_totalSize), 
		  EOSFlag(_EOSFlag), methodFlag(_methodFlag) {}
	~CTask();					
	void		load(char *fName);		// ������� ������� ������ �� �����
	void		clear();				// ������� ������
	EOS			&getEOS() { return *eos; }	
	EOS			&getEOSGlass() { return *eosGlass; }	
	void		setEOS(EOS* newEOS) { eos = newEOS; } ;			
	int			getEOSFlag() { return EOSFlag; }
	CMethod		&getMethod() { return *mtd; }	
	Zone		&getZone(int i) { return zones[i]; }
	unsigned int getNumZones() { return nZones; }
	unsigned int getTotalSize() { return totalSize; }
	bool		getHydroStage() { return bHydroStage; }
	bool		getHeatStage() { return bHeatStage; }
	bool		getExchangeStage() { return bExchangeStage; }
	char	   *getOutputFilename() { return outputFileName; }
	char	   *getInputFilename() { return inputFileName; }
	const char *getFlowFilename() { return flowFileName; }
	char	   *getTaskName() { return taskName; }	
	int			getSourceFlag() { return sourceFlag; }
	int			getViscFlag() { return viscFlag; }	
	int			getMethodFlag() { return methodFlag; }	
	double		getTauPulse() { return tauPulse;}
	double		getFluence() { return fluence; }
	double		getDeltaSkin() { return deltaSkin; }
	double		getCourant() { return courant; }
	double		getMaxTime() { return maxTime; }
	TaskType type;

	EOSBin  *eosBin;			// ��������� �� ���������� ���, ���� �����������
private:
	void		buildFileNames(const char *inputName);
	const char *readStringParam(FILE *f, const char *name);
	double		readFloatParam(FILE *f, const char *name);
	int			readIntParam(FILE *f, const char *name);
	bool	bHydroStage;		// ����������� �������������?
	bool	bHeatStage;			// ����������� ����������� ����������������?
	bool	bExchangeStage;		// ����������� ����������-������ �����?
	EOS		*eos;				// ��������� ���������
	EOS		*eosGlass;			// ��������� ��������� ������	
	int		sourceFlag;			// �������� ������� � ��������� ������� (0 - ���, 1 - ��������, 2 - �������� �� ������).
	double  tauPulse;			// ������������ �������
	double  fluence;			// ������ -- �������, ����������� �������� �����������
	double  deltaSkin;			// ������� ����-����
	Zone	*zones;				// ��������� �� ������ ���	
	unsigned int nZones;				// ���������� ���
	double  maxTime;			// �����, �� �������� ������� ������
	CMethod	*mtd;				// ����� ������� - �����/�������
	int		viscFlag;			// ������������� �������� ( 0 - �� ������������, 1 - ������������).
	double  courant;			// ����� ������� (���������)

	int		totalSize;			// ��������� ���������� ����� �� ���� �����
	int		EOSFlag;			// ��� ���������� ��� -- ��� ������ (0 - ����������, 1 - �����������)
	int		methodFlag;			// ����, ������������ ��������� �����. 0 - �������, �������������� ����� ����������,
								// 1 - �����, ����� ���������������-������-��������, 2 - ��������� ����� (� ����������).

	char inputFileName[_MAX_PATH];
	char outputFileName[_MAX_PATH];
	char flowFileName[_MAX_PATH];
	char EOSDirName[_MAX_PATH];  // ��� ���������� ��� -- ������� � table_data, � ������� ����� �������
	char taskName[_MAX_PATH];
};






#endif