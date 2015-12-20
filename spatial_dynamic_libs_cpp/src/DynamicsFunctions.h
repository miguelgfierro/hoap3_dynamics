//
// Author: Miguel González-Fierro <mgpalaci@ing.uc3m.es>, (C) 2011
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
//


#ifndef _Dynamics_Functions_H
#define _Dynamics_Functions_H

#include "ModelConstructors.h"

class df
{
public:
	
	float *Xj, *S, *tau, *a_grav, *a_grav_n, *f, *X,*v,*c,*a,*q,*qd,*qdd,*IA,*pA,*U, u1, *u, *d,*Xup,*pa,*Ia,*vJ,*IAfb,*pAfb,*afb,*avp,*fvp,*C,*H,*IC,*ICfb, *pCfb,*pC,*fh,*qdd_out, *tau_out,*f_ext, *afb_idf, *tau_idf;
	float *qdd_fdf, *afb_fbf, *Iafb, *pafb, *afb_fdf, d1;
	double *Xj_d, *S_d, *tau_d, *a_grav_d, *a_grav_n_d, *f_d, *X_d,*v_d,*c_d,*a_d,*q_d,*qd_d,*qdd_d,*IA_d,*pA_d,*U_d, u1_d, *u_d, *d_d,*Xup_d,*pa_d,*Ia_d,*vJ_d,*IAfb_d,*pAfb_d,*afb_d,*avp_d,*fvp_d,*C_d,*H_d,*IC_d,*ICfb_d, *pCfb_d,*pC_d,*fh_d,*qdd_out_d, *tau_out_d,*f_ext_d;
	double *pafb_d, *Iafb_d;

	df();
	void jcalc (float pitch, float q_i);

	float* ID(mc* model, float* q_i, float* qd_i, float* qdd_i);
	float* ID(mc* model, float* q_i, float* qd_i, float* qdd_i, df* f_ext, float* grav_accn = 0);

	void ID_force(double* tau, double* Fx, double* Fy, double* Fz, mc* model, double* q_i, double* qd_i, double* qdd_i);
	void ID_force(double* tau, double* Fx, double* Fy, double* Fz, mc* model, double* q_i, double* qd_i, double* qdd_i, df* f_ext, double* grav_accn = 0);

	void IDf(mc* model, float* Xfb, float* vfb, float* q_i, float* qd_i, float* qdd_i);
	void IDf(mc* model, float* Xfb, float* vfb, float* q_i, float* qd_i, float* qdd_i, df* f_ext, float* grav_accn = 0);

	void fwdkin (float* q_i, float* qd_i, float* qdd_i);
	void invkin (float* X, float* v, float* a);

	float* FDab (mc* model, float* q_i, float* qd_i, float* tau);
	float* FDab (mc* model, float* q_i, float* qd_i, float* tau, df* f,float* grav_accn = 0);

        void FDf (mc* model, float* Xfb, float* vfb, float* q_i, float* qd_i, float* tau, float* f_ext=0, float* grav_accn=0);

	void HandC (mc* model, float* q_i, float* qd_i, float* f_ext = 0, float* grav_accn = 0);

	float* FDcrb (mc* model, float* q_i, float* qd_i, float* tau = 0, float* f_ext = 0, float* grav_accn = 0);

	void HD (mc* model, float* fd, float* q_i, float* qd_i, float* qdd_i, float* tau);
	void HD (mc* model, float* fd, float* q_i, float* qd_i, float* qdd_i, float* tau, df* f_ext = 0, float* grav_accn = 0);


private:
	int i,j;
	
	float* v_1;
	float* a_1;
	double c4,c5,c6,s4,s5,s6,s4d,s5d,c4d,c5d;
	float* omega;
	float* omegad;
	int external_force;
	
};

#endif
