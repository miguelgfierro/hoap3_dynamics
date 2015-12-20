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

#include <iostream>
#include "Matrix.h"
#include "ArrayRelease.h"
#include "PlanarVectorModelConstructors.h"
#include "PlanarVectorDynamicsFunctions.h"


using namespace std;

float* pvdf::FDabp(pvmc *model, float *q, float *qd, float *tau, float* f_ext, float* grav_accn)
{
	pvdf* pvdf_aux = new pvdf [model[0].NB];
	pva pva_aux;
	matrix matrix_aux;

	float* a_grav1 = NULL;

	qdd = new float [model[0].NB];

	if (grav_accn == 0)
	{
		float a_grav_neg[3] = {0,0,0};
		a_grav1 = a_grav_neg;
	}
	else
	{
		float a_grav_neg[3] = {0,-grav_accn[0],-grav_accn[1]};
		a_grav1 = a_grav_neg;
	}

	if (f_ext != NULL) 
	{
		external_force = 1;
	}

	for (i=0;i<model[0].NB;i++)
	{
		int temp = model[i].parent;

		pvdf_aux[i].jcalcp(model[i].jcode,q[i]);
		pvdf_aux[i].vJ = matrix_aux.ScalarMulti(pvdf_aux[i].S,0,3,qd[i]);
		pvdf_aux[i].Xup = matrix_aux.Multiplication(pvdf_aux[i].Xj,3,3,model[i].Xtree,3,3);

		if (model[i].parent == 0)
		{
			pvdf_aux[i].v = pvdf_aux[i].vJ;
			pvdf_aux[i].c = matrix_aux.Zeros(0,3);
		}
		else 
		{	
			int temp = model[i].parent - 1;
			float* temp2 = matrix_aux.Multiplication(pvdf_aux[i].Xup,3,3,pvdf_aux[temp].v,0,3);

			pvdf_aux[i].v = matrix_aux.Sum(temp2,pvdf_aux[i].vJ);
			pvdf_aux[i].c = matrix_aux.Multiplication(pva_aux.crmp(pvdf_aux[i].v),3,3,pvdf_aux[i].vJ,0,3);
		}
		
		pvdf_aux[i].IA = model[i].I;

		cout <<"ia: "<<endl;
		matrix_aux.Display(pvdf_aux[i].IA,3,3);
		
		float* crf = pva_aux.crfp(pvdf_aux[i].v);
		float* crf_I = matrix_aux.Multiplication(crf,3,3,model[i].I,3,3);
		pvdf_aux[i].pA = matrix_aux.Multiplication(crf_I,3,3,pvdf_aux[i].v,0,3);

		if (external_force == 1)
		{
			int as = f_ext[i];
			pvdf_aux[i].pA = matrix_aux.ScalarAdd(pvdf_aux[i].pA,3,as,1);
		}
	}
	

	for (i=model[0].NB-1;i>=0;i--)
	{
		pvdf_aux[i].U = matrix_aux.Multiplication(pvdf_aux[i].IA,3,3,pvdf_aux[i].S,0,3);
		pvdf_aux[i].d = matrix_aux.Multiplication(pvdf_aux[i].S,0,3,pvdf_aux[i].U,0,3);
		float* S_pA = matrix_aux.Multiplication(pvdf_aux[i].S,0,3,pvdf_aux[i].pA,0,3);

		float temp = tau[i] - S_pA[0];
		pvdf_aux[i].u1 = temp;

		if (model[i].parent != 0)
		{
			int temp = model[i].parent - 1;
			
			float* U_d = matrix_aux.ScalarMulti(pvdf_aux[i].U,0,3,pvdf_aux[i].d[0],1);
			float* U_div_d_t_U = matrix_aux.VectorToMatrix(U_d,3,pvdf_aux[i].U,3);
			
			pvdf_aux[i].Ia = matrix_aux.Sum(pvdf_aux[i].IA,U_div_d_t_U,2);

			float* U_u = matrix_aux.ScalarMulti(pvdf_aux[i].U,0,3,pvdf_aux[i].u1);
			float* U_u_d = matrix_aux.ScalarMulti(U_u,0,3,pvdf_aux[i].d[0],1);
			float* Ia_c = matrix_aux.Multiplication(pvdf_aux[i].Ia,3,3,pvdf_aux[i].c,0,3);
			float* pA_Ic_c = matrix_aux.Sum(pvdf_aux[i].pA,Ia_c);

			pvdf_aux[i].pa = matrix_aux.Sum(pA_Ic_c,U_u_d); 

			float* Xup_t = matrix_aux.Transponse(pvdf_aux[i].Xup,3,3);
			float* Xup_Ia =  matrix_aux.Multiplication(Xup_t,3,3,pvdf_aux[i].Ia,3,3);
			float* Xup_Ia_Xup = matrix_aux.Multiplication(Xup_Ia,3,3,pvdf_aux[i].Xup,3,3);
			float* Xup_t_pa = matrix_aux.Multiplication(Xup_t,3,3,pvdf_aux[i].pa,0,3);

			pvdf_aux[temp].IA = matrix_aux.Sum(pvdf_aux[temp].IA,Xup_Ia_Xup,3);
			pvdf_aux[temp].pA = matrix_aux.Sum(pvdf_aux[temp].pA,Xup_t_pa,4);
		}
	}


	for(i=0;i<model[0].NB;i++)
	{
		
		if (model[i].parent == 0)
		{
			float* Xup_agrav = matrix_aux.Multiplication(pvdf_aux[i].Xup,3,3,a_grav1,0,3);
			pvdf_aux[i].a = matrix_aux.Sum(Xup_agrav,pvdf_aux[i].c,4);
		}
		else
		{
			int temp = model[i].parent - 1;
			float* Xup_a = matrix_aux.Multiplication(pvdf_aux[i].Xup,3,3,pvdf_aux[temp].a,0,3);
			pvdf_aux[i].a = matrix_aux.Sum(Xup_a,pvdf_aux[i].c,4);
		}

		float* Ua = matrix_aux.Multiplication(pvdf_aux[i].U,0,3,pvdf_aux[i].a,0,3);
		
		float aux = Ua[0];
		float u_Ua = pvdf_aux[i].u1 - aux;

		qdd[i] = u_Ua/pvdf_aux[i].d[0];

		float* S_qdd = matrix_aux.ScalarMulti(pvdf_aux[i].S,0,3,qdd[i]);
		pvdf_aux[i].a = matrix_aux.Sum(pvdf_aux[i].a,S_qdd,4);
		
	}
	return qdd;
}