
#ifndef METHODEULER_H
#define METHODEULER_H


#include "methodold.h"


class CMethodEuler : public CMethodOld {
public:
	double gamma;
	CMethodEuler(EOSOld *_eos) : CMethodOld(_eos) { gamma = 1.4; }
	~CMethodEuler();

	void	matter2Flow(CFieldOld &ms);
	void	advanceFlow(CFieldOld &ms, double tau);
    void	advanceFlowVacuum(CFieldOld &ms, double tau);
	void	flow2Matter(CFieldOld &ms, double tau);
	void    flow2MatterVacuum(CFieldOld &ms, CFieldOld &ms_temp, double t, double tau);
	void	createGrid(CFieldOld &ms);
	void	deleteGrid();
	Matrix4 getOmega(Node &n);
	Matrix4 getOmegaInv(Node &n);
	Vector4 getLambda(Node &n);
	void	averageNode(Node &n1, Node &n2, Node &nav);
	void	updateNode(Node &n);
	void	fillLambda(Vector4 &Fm1, Vector4 &F0, Vector4 &Fp1, Vector4 &Fp2, Vector4 &L, double step);
	void	fillLambdaComponent(int i, double lambda, double criteria, double curant);
	Vector4 calcFlux(Matrix4 Omega, Matrix4 OmegaInv, Vector4 W_j_m, Vector4 W_j, Vector4 W_j_p, Vector4 W_j_p_p);
	Vector4 calcApprRPFlux(Vector4 W_j, Vector4 W_j_p, Node &n);
	// Производная dp/dro при постоянных ro*v и ro*E
	double getdpdro_rov_roE(double ro, double ti, double te, double v);

	// Производная dp/drov при постоянных ro и ro*E
	double getdpdrov_ro_roE(double ro, double ti, double te, double v);

	// Производная dp/droE при постоянных ro и ro*v
	double getdpdroE_ro_rov(double ro, double ti, double te, double v);
};



#endif
