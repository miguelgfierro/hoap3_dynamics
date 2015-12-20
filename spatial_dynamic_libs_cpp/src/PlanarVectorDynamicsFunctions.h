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



#ifndef _Planar_Vector_Dynamics_Functions_H
#define _Planar_Vector_Dynamics_Functions_H

#include "PlanarVectorModelConstructors.h"

class pvdf
{
public:
	float* Xj;
	float* S;
	float* qdd;
	float* vJ;
	float* tau;
	float* f;
	float* H;
	float* C;
	float* fh;
	float* IC;
	float* avp;
	float* fvp;

	pvdf();
	void jcalcp (float code, float q); 
	float* FDabp (pvmc* model, float* q, float* qd, float* tau, float*f_ext = 0, float* grav_accn = 0);
	float* FDcrbp (pvmc* model, float* q_i, float* qd_i, float* tau, float* f_ext = 0, float* grav_accn = 0);
	float* IDp (pvmc* model, float* q_i, float* qd_i, float* qdd_i, float* f_ext = 0, float* grav_accn = 0);
	void HandCp (pvmc* model, float* q_i, float* qd_i, float* f_ext = 0, float* grav_accn = 0);

private:
	int i,j;
	float* Xup;
	float* v;
	float* c;
	float* IA;
	float* pA;
	float* U;
	float* d;
	float* Ia;
	float* pa;
	float* a;
	float external_force;
	float u1;
	



};




#endif