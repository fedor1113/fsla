#define _CRT_SECURE_NO_WARNINGS

#include<string.h>

#include "defines.h"
#include "solver.h"
#include "C1DProblem.h"
#include "F1DSimulation.h"
#include "C1DBCs.h"
#include "F1DReconstruction.h"



char* INPUT_FOLDER = new char[_MAX_PATH];  //"calc/";
char* OUTPUT_FOLDER = new char[_MAX_PATH]; //"calc/output/";

//#include <vld.h>

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cmath>

int main(int argc, char *argv[]) {
	if(argc > 1) {
		strcpy(INPUT_FOLDER, argv[1]);
		strcpy(OUTPUT_FOLDER, INPUT_FOLDER);
		strcat(OUTPUT_FOLDER, "output/");
	} else {
		strcpy(INPUT_FOLDER, "calc/");
		strcpy(OUTPUT_FOLDER, "calc/output/");
	}
	cout << "FSLA1D: hydrocode for numerical simulations in 1D-geometry v.0.1." << endl;
	cout << "Author: Vadim V. Shepelev, ICAD RAS, e-mail: vadim.v.shepelev@gmail.com" << endl;
	cout << "=======================================================================" << endl;
	string outputDir = string("output");		
	// Uncomment for NB EOS test problem
	// CEOSMieGruneisenAl eos = CEOSMieGruneisenAl();
	//C1DProblem pr = prNBtest;
	// Uncomment for Toro #1 test problem with ideal EOS
	//CEOSIdeal eos = CEOSIdeal(3.9);
	//CEOSIdeal eosAl = CEOSIdeal(3.9); 
	//C1DProblem pr = prLaserVTAlIdealTest1;
	//C1DField *fldptr = new C1DField(pr);
	// Uncomment for exact solver based Godunov-type method
	//CExactRiemannSolver ex;
	//C1DGodunovTypeMethod mtd = C1DGodunovTypeMethod(ex);












/*
	CSolver *s = new CSolver;
	s->goEuler("task-toro-5.txt"); // ��� ��������� �����
	delete s; 
	*/

	







	// Uncomment for LaserVT test problem
    // FEOSMGAlPrecise6 eos;
	// FEOSMieGruneisenAl eos;
	// FEOSIdeal eos = FEOSIdeal(3.9);
	FEOSIdeal eos = FEOSIdeal(1.4);
	C1DProblem pr = prDenisenko;
	C1DField *fldptr = new C1DField(pr);
    CHLLRiemannSolver hll;
	CHLLCRiemannSolver hllc;
	CLFRiemannSolver lf;
	CGPSRiemannSolver gps;
	CRoeRiemannSolver roe;
	CRoeGeneralRiemannSolver roegen;
	CBGKRiemannSolver bgk;
	CExactRiemannSolver ex;
	F1DENO2Reconstruction eno2rec=F1DENO2Reconstruction(*fldptr);
	C1D2ndOrderMethod mtd = C1D2ndOrderMethod(roe, eno2rec);	
	//C1DGodunovTypeMethod mtd = C1DGodunovTypeMethod(ex);
	//C1DBGKMethod mtd = C1DBGKMethod(bgk);
	
	//C1DLFMethod mtd = C1DLFMethod(lf);
	double _dtt[] = {pr.tmin, pr.tmax};
	vector<double> dtt = vector<double>(_dtt, _dtt+sizeof(_dtt)/sizeof(double));
	COutput outp = COutput(pr, outputDir, dtt);
	F1DSimulation sim = F1DSimulation(pr, eos, *fldptr, mtd, outp);
	sim.run();
	delete fldptr;
	// Uncomment for ideal gas vs vacuum test
	/* //CEOSIdeal eos = CEOSIdeal(3.9);
	CEOSIdeal eos = CEOSIdeal(2.5);
	C1DProblem pr =  prLaserVTAlIdealTest2; //prIdealVacTest;
	C1DField *fldptr = new C1DField(pr);
	CExactRiemannSolver exrslv;
	C1DGodunovTypeMethodVacuum gdn = C1DGodunovTypeMethodVacuum(exrslv, pr.x0);
	// C1DGodunovTypeMethod gdn = C1DGodunovTypeMethod(exrslv);
	double _dtt[] = {pr.tmin, pr.tmax};
	vector<double> dtt = vector<double>(_dtt, _dtt+sizeof(_dtt)/sizeof(double));
	COutput outp = COutput(pr, outputDir, dtt);
	F1DSimulation sim = F1DSimulation(pr, eos, *fldptr, gdn, outp);
	sim.run();
	delete fldptr;	*/

	// Uncomment for Toro #1 test problem with ideal EOS
/*	CEOSIdeal eos = CEOSIdeal(1.4);
	C1DProblem pr = prToro1Idealtest;
	C1DField *fldptr = new C1DField(pr);
	CHLLCRiemannSolver hllc;
	F1DENO2Reconstruction eno2rec=F1DENO2Reconstruction(*fldptr);
	C1D2ndOrderMethod mtd = C1D2ndOrderMethod(hllc, eno2rec);
	double _dtt[] = {pr.tmin, pr.tmax};
	vector<double> dtt = vector<double>(_dtt, _dtt+sizeof(_dtt)/sizeof(double));
	COutput outp = COutput(pr, outputDir, dtt);
	F1DSimulation sim = F1DSimulation(pr, eos, *fldptr, mtd, outp);
	sim.run();
	delete fldptr;*/	


	// Uncomment for metal problems
	// CSolver s = CSolver();
	// s->goGlass("task-Ru-glass.txt");
	//s->goGlass("task-Ru-glass-optic-1000.txt");
	//s->goGlass("task-Ru-glass-optic-2000.txt");
	//s->goGlass("task-Ru-glass-optic-3000.txt");
	//s->goGlass("task-Fe-glass.txt");

	//s->goGlass("task-Au-water-simple.txt");
	//s->goGlass("task-Au-water.txt");
	//s->goGlass("task-Au-water-vacuum.txt");
	
	//s->goGlass("task - Ni.txt");
	//s->goGlass("task.txt"); // ��� ������ � ������
	//s->go("task-5Si.txt");
	//s->goAuSpall("task.txt"); // ��� ������
	// s.goEuler("task-toro-1.txt"); // ��� ��������� �����
	//s->goEulerMovingMesh("task.txt"); // ��� ��������� ����� c ���������� ������
	//s->goEuler("task-LH1D.txt");          // ������ LH (������-������-������), ���������� �����������
    //s->goEuler("task-LH1D-p=123GPA.txt"); // ������ LH (������-������-������), ���������� �����������, � ����� ������ ����������
	
	// s->goEuler("task-eosbin-test-2.txt"); // ���� �� ���������� ��� �� ���� -- �� �� ���� �� �������� ��������� �������� ������ � ��������� ���
	//CSolver *s = new CSolver;
	//s->goEuler("task-laservt-ideal-test.txt"); // ���� �� �������� ��������� ��������� ������ � ��� �� �.�. 
	//s->goEuler("task-eosbin-toro-test-5.txt"); // ���� �� ���������� ��� (��� ������� ���������� ������ �������� ��� ���������)

	//s->goEuler("task-LH1D-aux-1.txt"); // ������ LH (������-������-������), ����� ������ ������-������
	//s->goEuler("task-eosbin-test-1.txt"); // ������ ���� ��������� �� ����������� ��������� ���������
	// Uncomment for Euler problems
	//s->goEuler("task-eosbin-toro-test-1.txt"); 
	//s->goEuler("task-test-NB.txt");
	// Uncomment for HLL flux Toro test 
	/*EOSBin eos = EOSBin(1.4, 0., 0.);	
	CTask prHLLTest = CTask(TaskType::RP1D, eos, 1., .75, 1., .125, 0., 1., 0., 1., 0., .2, .3, 100, .9, MethodType::hll);
    CSolver* s = new CSolver(prHLLTest);	
	s->goEuler();
	//
	delete s;*/

	///////////////////////////////////////
	// Uncomment for convergence rate calculation
	/*ofstream ofs, ofs1;
	ofs.open("conv-rate-runge.dat", ios::out);
	ofs << "TITLE = Convergence rates" << endl;
	ofs << "VARIABLES = \"h\",\"err_L1\",\"err_L2\",\"conv_Integral\"" << endl;
	ofs << "ZONE T=\"GPS\" I=6 F=POINT " << endl;
	ofs1.open("conv-rate-runge-all.dat", ios::out);
	ofs1 << "TITLE = Runge set of convergence rates for different schemes" << endl;
	ofs1 << "VARIABLES = \"h\",\"P\"" << endl;
	ofs1 << "ZONE T=\"BGK\" I=4 F=POINT" << endl;
	double f[] = {0., 0., 0., 0., 0., 0.}; 
	double h[] = {.01, .01/2., .01/4., .01/8., .01/16., .01/32.}; 
	unsigned counter = 0;
	CSolver *s = new CSolver;
	s->goEuler("task-toro-1.txt"); // ��� ��������� �����
	ofs << s->getdx() << " " << s->calcProblemL1NormRo() << " " << s->calcProblemL2NormRo() << " " << s->convIntegral << endl;
	f[counter++] = s->convIntegral;
	delete s;
	s = new CSolver;
	s->goEuler("task-toro-1-2.txt"); // ��� ��������� �����
	ofs << s->getdx() << " " << s->calcProblemL1NormRo() << " " << s->calcProblemL2NormRo() << " " << s->convIntegral << endl;
	f[counter++] = s->convIntegral;
	delete s;
	s = new CSolver;
	s->goEuler("task-toro-1-4.txt"); // ��� ��������� �����
	ofs << s->getdx() << " " << s->calcProblemL1NormRo() << " " << s->calcProblemL2NormRo() << " " << s->convIntegral << endl;
	f[counter++] = s->convIntegral;
	delete s;
	s = new CSolver;
	s->goEuler("task-toro-1-8.txt"); // ��� ��������� �����
	ofs << s->getdx() << " " << s->calcProblemL1NormRo() << " " << s->calcProblemL2NormRo() << " " << s->convIntegral << endl;
	f[counter++] = s->convIntegral;
	delete s;
	s = new CSolver;
	s->goEuler("task-toro-1-16.txt"); // ��� ��������� �����
	ofs << s->getdx() << " " << s->calcProblemL1NormRo() << " " << s->calcProblemL2NormRo() << " " << s->convIntegral << endl;
	f[counter++] = s->convIntegral;
	delete s;
	s = new CSolver;
	s->goEuler("task-toro-1-32.txt"); // ��� ��������� �����
	ofs << s->getdx() << " " << s->calcProblemL1NormRo() << " " << s->calcProblemL2NormRo() << " " << s->convIntegral << endl;
	f[counter++] = s->convIntegral;
	delete s;
	
	ofs1 << h[1] << " " << log10((f[0]-f[1])/(f[1]-f[2]))/log10(2.) << endl;
	ofs1 << h[2] << " " << log10((f[1]-f[2])/(f[2]-f[3]))/log10(2.) << endl;
	ofs1 << h[3] << " " << log10((f[2]-f[3])/(f[3]-f[4]))/log10(2.) << endl;
	ofs1 << h[4] << " " << log10((f[3]-f[4])/(f[4]-f[5]))/log10(2.) << endl;

	ofs.close();
	ofs1.close();*/
	///////////////////////////////////////

//	s = new CSolver;
//	s->go("al_glass_1000_400.txt");
//	delete s;


	//  s.go("test.txt");
	//  s.go("input6_euler.txt");
	//	s.testHeatStage("input_lagrange_heat_test.txt", "heat.dat");
	//	s.testExchangeStage("input_lagrange_exchange_test.txt", "exchange.dat");
	//  s.testGodunovScheme("input_godunov_test.txt");

/*	s->go("al_glass_testEOS_v200.txt");
	delete s;P

	s = new CSolver;
	s->go("al_glass_testEOS_v500.txt");
	delete s;

	s = new CSolver;
	s->go("al_glass_testEOS_v1000.txt");
	delete s;

	s = new CSolver;
	s->go("al_glass_testEOS_v2000.txt");
	delete s;

*/

	delete INPUT_FOLDER;
	delete OUTPUT_FOLDER;
	return 0;
}



