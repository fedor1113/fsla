#ifndef _CTask_H_
#define _CTask_H_

#include <stdio.h>
#include <stdlib.h>

#include "defines.h"
#include "method.h"
#include "eosold.h"
#include "CTestToro.h"
#include "eos\\EOSBin.h"
#include "cfield.h"

//#include "eosTableFeAlpha.h"

/* ���������, ������������ ����. �������������� ������� -- ����� ���. */

struct Zone  {
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

enum TaskType {undef, ruGlass, LH1D, auWater, MieGruneisenProblem};

enum SourceType {SrcUndef, SrcNone, SrcGlass, SrcMetal, SrcSq, Src5Layers};

enum MethodType {nomtd, samarskii, godunov1, eno2g, muscl, bgk, eno3g};

class CTask {
public:
	CTask() : type(TaskType::undef), bHydroStage(false), bHeatStage(false), bExchangeStage(false), 
		      eos(0), eosGlass(0), sourceFlag(SourceType::SrcUndef), tauPulse(0.), fluence(0.), deltaSkin(0.), 
			  zones(0), nZones(0), maxTime(0.), mtd(0), viscFlag(0), CFL(0.), totalSize(0), 
			  EOSFlag(0), methodFlag(MethodType::nomtd) {}
	CTask(TaskType _type, bool _bHydroStage, bool _bHeatStage, bool _bExchangeStage, EOSOld* _eos, EOSOld* _eosGlass, SourceType _sourceFlag,
		  double _tauPulse, double _fluence, double _deltaSkin, Zone* _zones, int _nZones, double _maxTime, CMethod* _mtd,
		  int _viscFlag, double _CFL, int _totalSize, int _EOSFlag, MethodType _methodFlag) :
		  type(_type), 
		  bHydroStage(_bHydroStage), bHeatStage(_bHeatStage), bExchangeStage(_bExchangeStage), 
		  eos(_eos), eosGlass(_eosGlass),
		  sourceFlag(_sourceFlag),
		  tauPulse(_tauPulse), fluence(_fluence), deltaSkin(_deltaSkin), 
		  zones(_zones), nZones(_nZones), 
		  maxTime(_maxTime),
		  mtd(_mtd), viscFlag(_viscFlag), CFL(_CFL), totalSize(_totalSize), 
		  EOSFlag(_EOSFlag), methodFlag(_methodFlag) {}
	~CTask();					
	void		load(char *fName);		// ������� ������� ������ �� �����
	void		clear();				// ������� ������
	EOSOld			&getEOS() { return *eos; }	
	EOSOld			&getEOSGlass() { return *eosGlass; }	
	void		setEOS(EOSOld* newEOS) { eos = newEOS; } ;			
	int			getEOSFlag() { return EOSFlag; }
	CMethod		&getMethod() { return *mtd; }	
	Zone		&getZone(int i) { return zones[i]; }
	unsigned int getNumZones() { return nZones; }
	unsigned int getTotalSize() { return totalSize; }
	bool		getHydroStage() { return bHydroStage; }
	bool		getHeatStage() { return bHeatStage; }
	bool		getExchangeStage() { return bExchangeStage; }
	string getOutputFilename() { return outputFileName; }
	string getInputFilename() { return inputFileName; }
	string getFlowFilename() { return flowFileName; }
	string getTaskName() { return taskName; }	
	SourceType	getSourceFlag() { return sourceFlag; }
	int			getViscFlag() { return viscFlag; }	
	MethodType  getMethodFlag() { return methodFlag; }		
	double		getTauPulse() { return tauPulse;}
	double		getFluence() { return fluence; }
	double		getDeltaSkin() { return deltaSkin; }
	double		getCFL() { return CFL; }
	double		getMaxTime() { return maxTime; }
	TaskType type;
	EOSBin  *eosBin;			// ��������� �� ���������� ���, ���� �����������
private:
	void		buildFileNames(string inputName);
	const char *readStringParam(FILE *f, const char *name);
	double		readFloatParam(FILE *f, const char *name);
	int			readIntParam(FILE *f, const char *name);
	bool	bHydroStage;		// ����������� �������������?
	bool	bHeatStage;			// ����������� ����������� ����������������?
	bool	bExchangeStage;		// ����������� ����������-������ �����?
	EOSOld		*eos;				// ��������� ���������
	EOSOld		*eosGlass;			// ��������� ��������� ������	
	SourceType sourceFlag;			// �������� ������� � ��������� ������� 
	double  tauPulse;			// ������������ �������
	double  fluence;			// ������ -- �������, ����������� �������� �����������
	double  deltaSkin;			// ������� ����-����
	Zone	*zones;				// ��������� �� ������ ���	
	unsigned int nZones;				// ���������� ���
	double  maxTime;			// �����, �� �������� ������� ������
	CMethod	*mtd;				// ����� ������� - �����/�������
	int		viscFlag;			// ������������� �������� ( 0 - �� ������������, 1 - ������������).
	double  CFL;			// ����� ������� (���������)
	int		totalSize;			// ��������� ���������� ����� �� ���� �����
	int		EOSFlag;			// ��� ���������� ��� -- ��� ������ (0 - ����������, 1 - �����������)
	MethodType methodFlag;	
	string taskName, inputFileName, outputFileName, flowFileName, EOSDirName; // EOSDirName ��� ���������� ��� -- ������� � table_data, � ������� ����� �������
};

#endif